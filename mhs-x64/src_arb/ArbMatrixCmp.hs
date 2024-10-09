module ArbMatrixCmp(main) where
import Prelude
import InputArbMatrixCmp

listeqArb :: [Integer] -> [Integer] -> Bool
listeqArb [] [] = True
listeqArb (x:xs) (y:ys) = x == y && listeqArb xs ys
listeqArb _ _ = False

matrixeqArb :: [[Integer]] -> [[Integer]] -> Bool
matrixeqArb [] [] = True
matrixeqArb (x:xs) (y:ys) = listeqArb x y && matrixeqArb xs ys
matrixeqArb _ _ = False

main :: IO ()
main = (matrixeqArb answer m) `seq` return ()
