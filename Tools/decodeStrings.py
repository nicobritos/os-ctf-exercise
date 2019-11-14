from __future__ import print_function
import os
import sys

# archivo a cargar tiene que contener pares de numeros en hexa (byte) y deben ser multiplo de 4 (leemos int)

DIVISOR = 0x56B


def read_input():
    s = 'Write filepath (can be relative) to decode or nothing to exit\nFilepath: '
    try:
        if (sys.version_info > (3, 0)):
            return input(s)
        else:
            return raw_input(s)
    except SyntaxError:
        return ''


# Doesn't save NULL
def parse_file(infile, outfile):
    hex_iterator = (int(c, 16) for c in infile.read())

    try:
        while True:
            i = m = n = 0
            while i < 4:
                j = b = 0
                while j < 2:
                    b |= next(hex_iterator)
                    if j == 0:
                        b <<= 4  # Nibble
                    j += 1
                m |= b
                if i < 3:
                    m <<= 8  # Byte
                i += 1

            # Invertimos el numero (maldito endianness)
            i = 0
            while i < 4:
                n |= m & 0xff
                if i < 3:
                    n <<= 8
                    m >>= 8
                i += 1

            if n > 0:
                n = int(n / DIVISOR)
                outfile.write(chr(n))
    except StopIteration:
        pass


def main():
    print('Python version: ' + str(sys.version_info[0]) + '.' + str(sys.version_info[1]))
    input_str = read_input()
    while input_str != '':
        try:
            with open(input_str, 'r') as infile:
                output_str = os.path.basename(input_str) + '.dec.txt'
                with open(output_str, 'w') as outfile:
                    parse_file(infile, outfile)
            print('Done "' + input_str + '"!')
        except Exception as e:
            print(e)

        input_str = read_input()

    print('Goodbye')


if __name__ == '__main__':
    main()
