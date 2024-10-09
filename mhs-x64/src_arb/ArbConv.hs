module ArbConv(main) where
import Prelude
import InputArbConv

kmul :: [Integer] -> [Integer] -> Integer
kmul (x:xs) (y:ys) = (x * y) + kmul xs ys
kmul _ _ = 0

mydrop :: Int -> [Integer] -> [Integer]
mydrop n xs = if n == 0 || null xs then xs else mydrop (n - 1) (tail xs)

conv :: Integer -> Int -> [Integer] -> [Integer] -> [Integer]
conv bias stride kernel vec =
    case vec of
        [] -> []
        _ -> (bias + kmul kernel vec):(conv bias stride kernel (mydrop stride vec))

listeqArb :: [Integer] -> [Integer] -> Bool
listeqArb [] [] = True
listeqArb (x:xs) (y:ys) = x == y && listeqArb xs ys
listeqArb _ _ = False

main :: IO ()
main = (listeqArb answer (conv bias stride kernel vec)) `seq` return ()
