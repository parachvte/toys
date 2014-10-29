# <Before Sunrise> 中，Jesse约Celine下火车的场景

# Add `say` and `aside` slot to Sequence
Sequence say := method(
    call sender name print
    ": " println
    "  " print
    self println
)

Sequence aside := method(
    "Aside: " print
    self println
)

# Conversations begin
Jesse := Object clone
Jesse name := "Jesse"
Jesse talk := method(
    "我有个疯狂的想法。如果现在不问问你，这会困扰我一辈子。" say
    yield
    "杰西有点儿紧张地看着赛琳，说不出话。" aside
    yield
    "我想继续这样跟你聊天。我是说，我不知道你的情形如何，但我感觉……我们是有缘分的。" say
    yield
    "那这样如何……我想让你跟我一起在维也纳下车。我们可以在城里逛逛。" say
    yield
    "我不知道。我只知道明天早上九点半我就要乘奥地利航空离开了，并且我也住不起旅馆，所以我们大概要整晚在外面逛了。如果你发现我是个疯子，可以随时离开，搭下一班火车走，对吧？" say
    yield
    "这样想吧，把时间往未来推10 年、20 年。你的婚姻已不像最初那样有激情，开始责怪自己的丈夫。你开始想起自己以前遇见过的人，那些你没有去主动追求的，想象着如果跟了其中之一事情会怎样。我就是那其中之一，好比你穿梭时空回到过去，看到自己错过了哪些事。你看，我这是给你和你未来老公帮了个大忙——给你一个机会，告诉你其实你也没错过什么，我其实跟他一样无聊没劲。当然希望不是这样。" say
    yield
)

Celine := Object clone
Celine name := "Celine"
Celine talk := method(
    yield
    "什么事？" say
    yield
    "赛琳很好奇，期待着他要说的事。" aside
    "到底什么？" say
    yield
    "我也觉得。" say
    yield
    "赛琳听后笑了，但还不完全确定。" aside
    "那我们干吗去？" say
    yield
    "她仍在考虑，没有回应。" aside
    yield
    "她微笑着，想了想现在的情况，然后站了起来。" aside
)


Jesse @@talk
Celine @@talk

Coroutine currentCoroutine pause
0
