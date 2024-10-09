module ArbMatrixMulConst(main) where
import Prelude
import InputArbMatrixMulConst

mul_to_list :: Integer -> [Integer] -> [Integer]
mul_to_list v l = case l of
    [] -> []
    (x:xs) -> (v * x):(mul_to_list v xs)

mul_to_matrix :: Integer -> [[Integer]] -> [[Integer]]
mul_to_matrix v m = case m of
    [] -> []
    (r:rs) -> (mul_to_list v r):(mul_to_matrix v rs)

listeqArb :: [Integer] -> [Integer] -> Bool
listeqArb [] [] = True
listeqArb (x:xs) (y:ys) = x == y && listeqArb xs ys
listeqArb _ _ = False

matrixeqArb :: [[Integer]] -> [[Integer]] -> Bool
matrixeqArb [] [] = True
matrixeqArb (x:xs) (y:ys) = listeqArb x y && matrixeqArb xs ys
matrixeqArb _ _ = False

main :: IO ()
main = (matrixeqArb answer (mul_to_matrix v m)) `seq` return ()
