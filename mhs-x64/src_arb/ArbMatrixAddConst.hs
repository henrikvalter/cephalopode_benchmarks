module ArbMatrixAddConst(main) where
import Prelude
import InputArbMatrixAddConst

add_to_list :: Integer -> [Integer] -> [Integer]
add_to_list v l = case l of
    [] -> []
    (x:xs) -> (v + x):(add_to_list v xs)

add_to_matrix :: Integer -> [[Integer]] -> [[Integer]]
add_to_matrix v m = case m of
    [] -> []
    (r:rs) -> (add_to_list v r):(add_to_matrix v rs)

listeqArb :: [Integer] -> [Integer] -> Bool
listeqArb [] [] = True
listeqArb (x:xs) (y:ys) = x == y && listeqArb xs ys
listeqArb _ _ = False

matrixeqArb :: [[Integer]] -> [[Integer]] -> Bool
matrixeqArb [] [] = True
matrixeqArb (x:xs) (y:ys) = listeqArb x y && matrixeqArb xs ys
matrixeqArb _ _ = False

main :: IO ()
main = (matrixeqArb answer (add_to_matrix v m)) `seq` return ()
