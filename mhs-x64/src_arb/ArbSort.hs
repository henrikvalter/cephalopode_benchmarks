module ArbSort(main) where
import Prelude
import InputArbSort

merge :: [Integer] -> [Integer] -> [Integer]
merge l1 [] = l1
merge [] l2 = l2
merge l1@(x:xs) l2@(y:ys) = if x < y then x:(merge xs l2) else if x > y then y:(merge l1 ys) else x:y:(merge xs ys)

split_list :: [Integer] -> ([Integer],[Integer])
split_list l =
    case l of
        [] -> ([],[])
        (x:xs) -> case xs of
            [] -> ([x],[])
            (y:ys) -> 
                let (as,bs) = split_list ys
                in (x:as, y:bs)

merge_sort :: [Integer] -> [Integer]
merge_sort l =
    case l of
        [] -> []
        [x] -> [x]
        _ -> let (xs,ys) = split_list l
             in merge (merge_sort xs) (merge_sort ys)

list_last :: [Integer] -> Integer
list_last [x] = x
list_last (x:xs) = list_last xs

res :: [Integer] -> Integer
res xs =
    let l = merge_sort xs
        first = head l
        last = list_last l
    in last - first

main :: IO ()
main = ((res xs) == answer) `seq` return ()
