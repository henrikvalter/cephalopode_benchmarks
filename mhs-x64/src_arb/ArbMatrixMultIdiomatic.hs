module ArbMatrixMultIdiomatic(main) where
import Prelude
import InputArbMatrixMult
--import Data.List (transpose)

hds :: [[Integer]] -> [Integer]
hds = map head

tls :: [[Integer]] -> [[Integer]]
tls = map tail

transp :: [[Integer]] -> [[Integer]]
transp foo = if null (head foo) then [] else (hds foo):(transp (tls foo))

dot :: [Integer] -> [Integer] -> Integer
dot xs ys = sum $ zipWith (*) xs ys

vmult :: [Integer] -> [[Integer]] -> [Integer]
vmult row cs = map (dot row) cs

mmultT :: [[Integer]] -> [[Integer]] -> [[Integer]]
mmultT m1 m2t = map (\r -> vmult r m2t) m1

mmult :: [[Integer]] -> [[Integer]] -> [[Integer]]
mmult m1 m2 = mmultT m1 (transp m2)

listeqArb :: [Integer] -> [Integer] -> Bool
listeqArb [] [] = True
listeqArb (x:xs) (y:ys) = x == y && listeqArb xs ys
listeqArb _ _ = False

matrixeqArb :: [[Integer]] -> [[Integer]] -> Bool
matrixeqArb [] [] = True
matrixeqArb (x:xs) (y:ys) = listeqArb x y && matrixeqArb xs ys
matrixeqArb _ _ = False

main :: IO ()
main = (matrixeqArb answer (mmult m1 m2)) `seq` return ()
