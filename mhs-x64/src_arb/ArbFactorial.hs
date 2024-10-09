module ArbFactorial(main) where
import Prelude
import InputArbFactorial

factorial :: Integer -> Integer
factorial n = if n <= 1 then 1 else n * factorial (n - 1)

main :: IO ()
main = (factorial n == answer) `seq` return ()
--main = print (factorial n == answer)
