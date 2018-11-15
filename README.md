# castle_game
Use c++ to simulate multiple rounds of competition between each strategy.

First initialize each strategy, which total size about six million is still tolerable. 

Second, let the strategy to cambat with each other and calculate their average score. Rank the scores from large to small and eliminate the worse half strategies. During the early rounds, the total size is too big for a one-cycle match. so I let each strategy to combat with a few random strategies.

Finally, I output the top ten strategies for each round.
