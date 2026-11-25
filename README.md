glider shapes (4 directions x 4 phases): 16

compatible placements of a SE glider with another glider (out of 1260 per type):
  with SE: 4076 compatible placements (40 distinct column offsets, 7 row offsets)
  with NE: 4004 compatible placements (38 distinct column offsets, 7 row offsets)
  with SW: 0 compatible placements (0 distinct column offsets, 0 row offsets)
  with NW: 0 compatible placements (0 distinct column offsets, 0 row offsets)

[all gliders heading the same way (SE)] 12 gliders, verified over 1260 generations: YES
  mix: SE x12
.#.....#......#...........#..........#.......
.#......##.....##.....#......#........##....#
##.....##.....##.......##.....##.....##......
....#.................##.....##..........#...
.....#....#.#.....#..............#........##.
...###.....##......##....#.#......##.....##..
...........#......##......##.....##..........
  search finished (result is the maximum)

[right-moving mix: SE + NE (one down-right, one up-right)] 12 gliders, verified over 1260 generations: YES
  mix: NE x11 SE x1
.............................................
...###.......##.....##.....##.....##.....###.
.....#........##.....##.....##.....##......#.
....#....#...#......#......#......#.......#..
##........#......#......#......#......##.....
.#......###......##.....##.....##....#.#....#
.#..............#.#....#.#....#.#......#.....
  search hit the time limit (result is a lower bound)

[downward mix: SE + SW (one right, one left)] no valid set found

[fully opposite: SE + NW] no valid set found

[any directions] 11 gliders, verified over 1260 generations: YES
  mix: NE x10 SE x1
.........##.....##.....##...##...##.....##...
........#......#......#....#....#......#.....
............#......#................#........
....#.......##.....##...............##.....##
#....#.....#.#....#.#..............#.#......#
...###.....................................#.
........##.....##.....##...##...##.....##....
  search hit the time limit (result is a lower bound)

real	4m12.307s
user	4m29.663s
sys	0m0.022s
Shell cwd was reset to /home/claude
