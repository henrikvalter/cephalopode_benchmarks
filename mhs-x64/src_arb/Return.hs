module Return(main) where
import Prelude

main :: IO ()
main = True `seq` return ()
