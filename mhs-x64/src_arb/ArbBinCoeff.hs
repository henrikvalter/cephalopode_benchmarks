module ArbBinCoeff(main) where
import Prelude
import InputArbBinCoeff

factorial :: Integer -> Integer
factorial n = if n <= 1 then 1 else n * factorial (n - 1)

bincoeff :: Integer -> Integer -> Integer
bincoeff n k = factorial n `div` (factorial k * factorial (n - k))

main :: IO ()
main = (bincoeff n k == answer) `seq` return ()
--main = print (bincoeff n k == answer)
