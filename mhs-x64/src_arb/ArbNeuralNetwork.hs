module ArbNeuralNetwork(main) where
import Prelude
import InputArbNeuralNetwork

mul1 :: [Integer] -> [Integer] -> Integer
mul1 (x:xs) (y:ys) = x*y+(mul1 xs ys)
mul1 [] [] = 0

mmult :: [[Integer]] -> [Integer] -> [Integer]
mmult (r:rs) v = (mul1 r v):(mmult rs v)
mmult [] v = []

reLU :: [Integer] -> [Integer]
reLU (v:vs) = (if v >= 0 then v else 0):(reLU vs)
reLU [] = []

nn_stage :: [[Integer]] -> [Integer] -> [Integer]
nn_stage mat v = reLU (mmult mat v)

neuralNetwork :: [[[Integer]]] -> [Integer] -> [Integer]
neuralNetwork (mat:mats) vec = neuralNetwork mats (nn_stage mat vec)
neuralNetwork [] vec = vec


main :: IO ()
main = ((head (neuralNetwork network vec)) == answer) `seq` return ()

