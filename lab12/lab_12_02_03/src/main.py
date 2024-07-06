import tkinter as tk
from tkinter import messagebox, filedialog
from lib import generate_prime_numbers, insert_after_even1, insert_after_even2

def about():
    messagebox.showinfo("О программе",
                        "Вариант работы - третий"
                        )

def showerror(string):
    messagebox.showerror("ОШИБКА", string)

def help_me():
    messagebox.showinfo("Справка",
"""1) Чтобы получить первые N простых чисел, введите число N в поле ввода и нажмите кнопку\n
2) Чтобы вставить число в массив по правилу, введите сначала вставляемое число и потом массив\n
3) Ввод всех чисел  производится через пробел в поле ввода\n
4) В случае неудачи в поле 'Статус' выводится ошибка и ее причины\n
5) Чтобы изменить библиотеку, в пункте меню сверху выберите \"Задание\", потом\"Изменить библиотеку\"\n
6) Чтобы изменить способ выделения памяти в функциях, в меню сверху выберите \"Задание\", потом \"Изменить тип функций\"
7) Чтобы выйти из программы, в пункте меню сверху выберите \"Выход\"\n"""
)


def swap_funcs():
    global func_insert_after_even
    global func_generate_prime_numbers
    if func_insert_after_even == None or func_generate_prime_numbers == None:
        func_insert_after_even = insert_after_even1
        func_generate_prime_numbers = generate_prime_numbers
    elif func_insert_after_even == insert_after_even1:
        func_insert_after_even = insert_after_even2
        func_generate_prime_numbers = generate_prime_numbers
    else:
        func_insert_after_even = insert_after_even1
        func_generate_prime_numbers = generate_prime_numbers

def GetEntry(entry):
    return entry.get()

def SetEntry(entry, string):
    entry.config(state="normal")
    entry.delete(0, tk.END)
    entry.insert(0, string)
    entry.config(state="disabled")


def CmdGetPrime(event):
    string = GetEntry(entry)
    if (len(string) == 0):
        # SetEntry(Text, "Ошибка! Введите только 1 число")
        showerror("Ошибка! Введите только 1 число")
        return;
    string = string.split(" ")
    if (len(string) != 1):
        # SetEntry(Text, "Ошибка! Введите только 1 число")
        showerror("Ошибка! Введите только 1 число")
        return;
    number = int(string[0])
    primes = func_generate_prime_numbers(number)
    # SetEntry(entry, " ".join(primes))
    listbox.delete(0, tk.END)
    for i in primes:
        listbox.insert(tk.END, f"{i:^50}")
    # SetEntry(Text, "Все хорошо")

def CmdInsertAfterEven(event):
    string = GetEntry(entry)
    if (len(string) == 0):
        # SetEntry(Text, "Ошибка! Введите число и массив")
        showerror("Ошибка! Введите вставляемое число и массив через пробел")
        return;
    string = string.split(" ")
    if (len(string) < 2):
        # SetEntry(Text, "Ошибка! Введите число и массив")
        showerror("Ошибка! Введите вставляемое число и массив через пробел")
        return;
    
    string = list(map(int, string))
    try:
        newlist = func_insert_after_even(string[1:], string[0])
    except Exception as e:
        # SetEntry(Text, f"Ошибка! {e}")
        showerror(f"Ошибка! {e}")
        return;
    listbox.delete(0, tk.END)
    for i in newlist:
        listbox.insert(tk.END, f"{i:^50}")
    # SetEntry(Text, "Все хорошо")

def GetLibPath():
    path = filedialog.askopenfilename(title="Выберите динамическую библиотеку", filetypes=(("so файлы", "*.so"), ("Все файлы", "*.*")))
    if path:
        print(path)
window = tk.Tk()
window.title("Лабораторная работа 12")
window.geometry("600x450")

# load_lib("out/libprocess.so")

# generate_prime_numbers, insert_after_even1, insert_after_even2 = load_lib("../out/libprocess.so")

func_generate_prime_numbers = None
func_insert_after_even = None

swap_funcs()

print(func_generate_prime_numbers, func_insert_after_even)

menu_bar = tk.Menu(window)

Helpmenu = tk.Menu(menu_bar, tearoff=0)
Helpmenu.add_command(label="О программе", command=about)
Helpmenu.add_command(label="Справка", command=help_me)
Helpmenu.add_separator()
Helpmenu.add_command(label="Выход", command=window.quit)

Taskmenu = tk.Menu(menu_bar, tearoff=0)
Taskmenu.add_command(label="Изменить библиотеку", command=GetLibPath)
Taskmenu.add_command(label="Изменить тип функций", command=swap_funcs)

menu_bar.add_cascade(label="Помощь и справка", menu=Helpmenu)
menu_bar.add_cascade(label="Задание", menu=Taskmenu)
menu_bar.add_command(label="Выход/завершить работу программы", command=window.quit)
window.config(menu=menu_bar)

entry = tk.Entry(window, width=5, font=("Arial", 12))
entry.grid(row=0, column=0, sticky="wse", padx=15, pady=15)

button = tk.Button(window, font=("Arial", 12),text="Формирование n простых чисел", width=25, height=7)
button.bind("<Button-1>", CmdGetPrime)
button.grid(row=3, column=2, rowspan=2, columnspan=2, sticky="nw", padx=15, pady=5)

button2 = tk.Button(window, font=("Arial", 12),text="Вставка после четных", width=25, height=7)
button2.bind("<Button-1>", CmdInsertAfterEven)
button2.grid(row=1, column=2, rowspan=2, columnspan=2, sticky="nw", padx=15, pady=5)

listbox = tk.Listbox(window, width=25, height=10, font=("Times New Roman", 16))
listbox.grid(row=1, column=0, rowspan=15, sticky="wn", padx=5, pady=5)

window.mainloop()
