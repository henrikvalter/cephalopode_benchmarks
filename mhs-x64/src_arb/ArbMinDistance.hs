module ArbMinDistance(main) where
import Prelude
import InputArbMinDistance

square :: Integer -> Integer
square x = x*x

sqdistance :: [Integer] -> [Integer] -> Integer
sqdistance (x1:y1:z1:r1) (x2:y2:z2:r2) =
    square (x1-x2) + square (y1-y2) + square (z1-z2)
sqdistance _ _ = 0

min_distance :: [[Integer]] -> [Integer] -> Integer
min_distance (x1:rem_locs) my_loc =
    let cur = sqdistance x1 my_loc in
    let rem = min_distance rem_locs my_loc in
    if (rem >= cur) then cur else rem
min_distance [] my_loc = 100

main :: IO ()
main = ((min_distance locs my_loc) == answer) `seq` return ()
