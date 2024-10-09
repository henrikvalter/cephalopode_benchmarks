module ArbSearch(main) where
import Prelude
import InputArbSearch

search :: Integer -> [Integer] -> [Integer]
search _ [] = []
search key (x:xs) =
    if key == x then x:(search key xs) else search key xs

main :: IO ()
main = ((sum $ search key xs) == answer) `seq` return ()
