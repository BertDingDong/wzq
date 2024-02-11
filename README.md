# 国科大C语言程序设计与实验五子棋大作业
---
>本人的五子棋大作业包含五个文件，分别是wzq-s2.c（main函数，五子棋运行的主要部分），ai2.c（ai文件，表示ai落子逻辑，实际上是第9代ai，由于多次迭代，直接将原来旧版的ai文件改了名），score6.c（得分函数，用于计算单点得分）
>ban.c（禁手函数，其中只考虑一层复杂禁手），ku.h（库函数，包含了一些全局使用的变量如棋盘情况，得分棋盘，以及一些棋形的得分），以下是设计思路介绍以及一些想法
## 主函数
- 主函数的主要功能就是支撑起整个五子棋游戏的进行
- 大体思路就是，用一个无限循环来实现反复落子，并且在可以判出胜负时结束循环
- 自然，判胜函数也在主函数中
  
  >在实现判胜函数过程中，值得注意的是如果考虑禁手的情况下，黑棋的判断顺序为：是否长连？是否获胜？是否出现33或44禁手？因此判胜需要将黑棋跟白棋的判胜区分开来，并且实战中
  >会发现出现ai被迫进行防御时，触发禁手规则将自己判负的情况，为此我特地将ai的判胜也区分出来，ai的判胜不考虑禁手，避免ai将自己判负的情况出现
  
## ai函数
- ai采用的思路是武老师上课提到的高级策略：考虑自己和对方的多次落子，并且对每次落子进行打分，选取最优解
  
  >实际上这个过程涉及到的是一个MinMax算法，也就是在自己落子时考虑最优情况，在对方落子时考虑最坏情况，实践中我选择的是将自己走的每一步的得分相加，再减去对方走的每一步的得分，作为最后的总分
  >这个算法考虑的接下来的步数越多，所需要的算力也就越大，并且我认为奇数层的思考是缺乏理性的（不考虑防守的进攻是无意义的），因此每次增加2层都会带来巨大的算力消耗

- 为了抵消这种算力消耗，我采用了以下一些技巧：
- Alpha-Beta剪枝

  >Alpha-Beta剪枝的原理在于：若已知某个max节点得分，在其后两层发现一个比该节点目前得分还高的节点，则其后两层的后续搜索是无意义的
  >因为在我们选择该节点后，如果在下一层min层对方选择了会引发上述搜索的节点A，那么这时候我们的得分一定是会比已有的得分高的，换言之对方要让我们得分最小的目的就无法实现了
  >所以对方一定不会选择这个节点A，也就没必要考虑A下属的节点情况

- 最优路径搜索

  >在Alpha-Beta剪枝中，显而易见的是如果我们一开始就找到了最优的点，那么后续的节点就会很快的被剪枝删去
  >因此找到最优点（无论是对哪一边）的速度决定了Alpha-Beta剪枝的效果，我做了一个预处理，在搜索开始前，先将场上所有点位的分数从高到低进行排序
  >然后按这个顺序去进行搜索，就能更快找到最优的点了，也就大大加快了搜索速率

- 自定义搜索

  >这是一种比较危险的方法，相当于人工定义每层搜索点的个数，实际上我们可以保证最优点大概率会出现在场上得分最高的前十个点
  >因此我们在前两轮搜索中，人工地限制了搜索的数量，在搜索了10个点之后就停止搜索
  >第3,4轮中，由于第一轮对弈导致局势变化，先前的路径未必是最优的了，经过反复试验，将搜索的个数调至50个是相对安全的
  >第5,6轮中，由于搜索100个和全搜区别不大，故不加限制
  >这种方法是存在隐患的，一旦最优点没有被搜索到，就会造成机器棋力下降，会产生很严重的后果（比如被速杀），因此谨慎使用

- 实际上还有一些技术如使用哈希表来记录局面信息，算杀，冲四防御等没被用到，仍待后人改进，也欢迎来找我交流
## 禁手函数
- 禁手只针对黑棋生效，因此对于白棋默认不触发禁手即可
- 禁手需要判断长连，三三，四四三种情况，其中长连比较简单也浅显，只需要判断是否连接超过5个棋子即可
- 三三和四四关键在于判断是否成活三和是否成四连，其中活三的关键又在于是否能成活四，因此只需要用三个函数来判断对应点位是否会形成活三，冲四，活四即可
- 考虑复杂禁手的情况下，需要对禁手函数进行递归调用，实战中发现最复杂禁手也只调用了一层，因此我人工限制了禁手的递归次数，在进行一次递归后就不再考虑复杂禁手
## 得分函数
- 得分主要根据产生的棋型判断，并且根据高等棋型远大于低等棋型，活棋型等价于高一等堵住一头棋型来确定
- 由于采用的是点得分，根据一点最多被自己四个方向两边各4个点影响，我采用了链表来处理
- 进入得分函数后，先将四个方向的棋子情况计入到四个数组中，并且将边界视为对方的棋子
- 然后对单个方向上的棋型进行穷举，使用链表遍历四个方向后得到最终得分
- 得分函数非常重要！！！一旦棋型错判漏判就会导致出现昏着甚至输掉比赛
- 实际上对网上的ai进行研究后发现对整个局势的打分会比对单点的打分更有效且厉害，但是由于时间关系已经来不及修改了，留待后人改进
## 库函数
- 包含了一些基本的头文件，以及宏定义
- 并且把需要在不同文件中出现的重要结构如棋盘放入其中，方便不同函数使用
## 一些想法
卷五子棋确实是一件非常痛苦的事情，在五子棋设计的一个多月里，除去开发的一周，其他时间基本都在改各种各样的bug以及找人测试（甚至比赛前一个小时还与田昊洋同学进行私下PK，并且在比完后发现了一个得分函数中的bug）
过程中最大的心得就是，写代码过程中一定要时刻保持头脑清醒，不要寄希望于后面改bug时补救，找bug真的很难找到

附上一只一个月以来陪我不断训练的网上[ai](https://gomocalc.com/#/) ，可以自由修改思考层数以及禁手规则等，非常适合做自己的ai的陪练

感谢五子棋开发过程中与我进行友谊切磋以及交流思路的各位同学为我提供了宝贵的实战经验，感谢网络上各种各样的五子棋教程让我集百家之长，感谢武老师以及助教在开发过程中给予的指导

希望这篇略显粗糙的五子棋思路介绍能给在期末周还要焦头烂额地卷五子棋的你一些帮助
