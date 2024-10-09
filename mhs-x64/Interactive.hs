module Interactive(module Interactive) where
import Prelude
import System.IO.PrintOrRun
default (Integer, Double, String, ())

_it = fromRational
_itIO = printOrRun _it
