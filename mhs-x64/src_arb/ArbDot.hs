module ArbDot(main) where
import Prelude
import InputArbDot

dot :: [Integer] -> [Integer] -> Integer
dot [] _ = 0
dot _ [] = 0
dot (x:xs) (y:ys) = (x * y) + dot xs ys

main :: IO ()
main = (dot xs ys == answer) `seq` return ()
--main = print (dot xs ys == answer)
