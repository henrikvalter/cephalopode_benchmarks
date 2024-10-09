module ArbMatrixMult(main) where
import Prelude
import InputArbMatrixMult

hds :: [[Integer]] -> [Integer]
hds l = map head l

tls :: [[Integer]] -> [[Integer]]
tls l = map tail l

transp :: [[Integer]] -> [[Integer]]
transp foo = if null (head foo) then [] else (hds foo):(transp (tls foo))

dot :: [Integer] -> [Integer] -> Integer
dot (x:xs) (y:ys) = (x * y) + dot xs ys
dot _ _ = 0

vmult :: [Integer] -> [[Integer]] -> [Integer]
vmult row cols = 
    case cols of
        [] -> []
        (c:cs) -> (dot row c):(vmult row cs)

mmultT :: [[Integer]] -> [[Integer]] -> [[Integer]]
mmultT m1 m2t =
    case m1 of
        [] -> []
        (r:rs) -> (vmult r m2t):(mmultT rs m2t)

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
