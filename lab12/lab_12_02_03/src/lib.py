from tkinter import filedialog, messagebox
from sys import exit
import ctypes as C99

try:
    lib = C99.CDLL("../out/libprocessss.so")
except Exception:
    while True:
        path = filedialog.askopenfilename(title="Выберите динамическую библиотеку", filetypes=(("so файлы", "*.so"), ("Все файлы", "*.*")))
        if path:
            try:
                lib = C99.CDLL(path)
                break
            except Exception:
                continue
        else:
            messagebox.showerror("Ну, попробуйте еще", "Библиотека не выбрана, программа завершает свою работу")
            exit()

#int generate_prime_numbers(long long *,size_t size);
_generate_prime_numbers = lib.generate_prime_numbers
_generate_prime_numbers.argtypes = (C99.POINTER(C99.c_longlong), C99.c_size_t)
_generate_prime_numbers.restype = C99.c_int;

def generate_prime_numbers(n):
    """
    Генерирует список простых чисел до заданного количества.

    Аргументы:
        n (int): кол-во простых чисел.

    Возвращает:
        list: Список простых чисел до индекса 'n'. Если простых чисел не найдено или случилась ошибка, возвращается пустой список.
    """
    size = C99.c_size_t(n)
    primelist = (C99.c_longlong * n)()
    test = _generate_prime_numbers(primelist, size)
    if test == 0:
        return primelist
    return []
    

#int insert_after_even(int *original, size_t n, int *new_array, size_t *k, int num);
_insert_after_even = lib.insert_after_even
_insert_after_even.argtypes = (C99.POINTER(C99.c_int), C99.c_size_t, C99.POINTER(C99.c_int), C99.POINTER(C99.c_size_t), C99.c_int)
_insert_after_even.restype = C99.c_int

def insert_after_even1(list, k):
    """
    Вставляет заданное целое число `k` после каждого четного числа во входном списке.
    
    Аргументы:
        list (List[int]): Входной список целых чисел.
        k (int): Число, которое будет вставлено после каждого четного числа.
        
    Возвращает:
        List[int]: Измененный список с вставленным `k` после каждого четного числа. Если входной список пуст или в нем нет четных чисел, возвращается пустой список.
    """
    len_src = len(list)
    src = (C99.c_int * len_src)(*list)
    new_len = C99.c_size_t(0)
    test = _insert_after_even(src, len_src, None, new_len, k)
    if test == 1:
        dst = (C99.c_int * new_len.value)()
        test = _insert_after_even(src, len_src, dst, new_len, k)
        return dst
    else:
        return []

def insert_after_even2(list, k):
    len_src = len(list)    """
    Вставляет заданное целое число `k` после каждого четного числа во входном списке.
    
    Аргументы:
        list (List[int]): Входной список целых чисел.
        k (int): Число, которое будет вставлено после каждого четного числа.
        
    Возвращает:
        List[int]: Измененный список с вставленным `k` после каждого четного числа. Если входной список пуст или в нем нет четных чисел, возвращается пустой список.
    """

    src = (C99.c_int * len_src)(*list)
    new_len = C99.c_size_t(len_src + len([x for x in list if x % 2 == 0]))
    dst = (C99.c_int * new_len.value)()
    test = _insert_after_even(src, len_src, dst, new_len, k)
    if test == 0:
        return dst
    else:
        return []
