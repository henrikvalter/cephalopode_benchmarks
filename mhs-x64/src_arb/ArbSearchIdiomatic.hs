module ArbSearchIdiomatic(main) where
import Prelude
import InputArbSearch

search :: Integer -> [Integer] -> [Integer]
search key = filter (== key)

main :: IO ()
main = ((sum $ search key xs) == answer) `seq` return ()
