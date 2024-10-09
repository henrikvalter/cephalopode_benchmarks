
# cp -t src_fixed src_arb/Arb*.hs
# rename Arb Fixed src_fixed/*
#
# for x in src_fixed/*.hs; do
#     sed -i 's/Integer/Int/g' "$x"
#     sed -i 's/Arb/Fixed/g' "$x"
# done

import os
import subprocess

def main():
    for f in os.listdir("src_arb/"):
        if f.startswith("Arb"):
            new_filename = f"Fixed{f[3:]}"
            #print(f"Copying src_arb/{f} into src_fixed/{new_filename}")
            subprocess.run(["cp", f"src_arb/{f}", f"src_fixed/{new_filename}"])
            #print(f"Replacing Integer with Int in src_fixed/{new_filename}")
            subprocess.run(["sed", "-i", "s/Integer/Int/g", f"src_fixed/{new_filename}"])
            subprocess.run(["sed", "-i", "s/Arb/Fixed/g", f"src_fixed/{new_filename}"])

if __name__ == "__main__":
    main()
