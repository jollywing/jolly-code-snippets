
# given a decimal, convert it to hexadecimal.
hex_dict = {10:'a', 11:'b', 12:'c', 13:'d', 14:'e', 15:'f'}
decimal_dict = {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6,
                '7':7, '8':8, '9':9, 'a':10, 'b':11, 'c':12,
                'd':13, 'e':14, 'f':15}

def dec_to_hex(n):
    str = ''
    while n >= 16:
        r = n % 16
        n = n // 16
        if r >= 10:
            r = hex_dict[r]
        str = '{}{}'.format(r, str)

    if n >= 10:
        n = hex_dict[n]
    str = '0x{}{}'.format(n, str)
    return str

def hex_to_dec(hex_str):
    hex_str = hex_str.lower()
    if hex_str.startswith('0x'):
        hex_str = hex_str.lstrip('0x')

    r = 0
    for i in range(len(hex_str)):
        factor = 1
        for j in range(len(hex_str) - 1 - i):
            factor *= 16
        r += decimal_dict[hex_str[i]] * factor
    return r

if __name__ == '__main__':
    input_num = input('Input a decimal number:')
    n = int(input_num)
    hex_str = dec_to_hex(n)
    print('The Hex string: {}'.format(hex_str))

    input_str = input('Input a Hex string:')
    n = hex_to_dec(input_str)
    print('The decimal result: {}'.format(n))
