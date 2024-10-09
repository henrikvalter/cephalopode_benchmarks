module ArbDerivative(main) where
import Prelude
import InputArbDerivative

derivative :: [Integer] -> [Integer]
derivative (x1:t@(x2:xs)) = (x2 - x1):(derivative t)
derivative _ = []

main :: IO ()
main = ((sum $ derivative xs) == answer) `seq` return ()
--main = print ((sum $ derivative xs) == answer)
