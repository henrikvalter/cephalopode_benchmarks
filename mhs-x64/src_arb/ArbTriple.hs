module ArbTriple(main) where
import Prelude
import InputArbTriple

triple :: Integer -> Integer
triple n = if n == 0
    then 1
    else
        let x = triple (n - 1)
        in x + x + x

main :: IO ()
main = (triple n == answer) `seq` return ()
--main = print (triple n == answer)

