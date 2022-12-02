from tkinter import *
from tkinter import messagebox as MessageBox

NUMERO_TIRADORES = 1
SERIE = 1
TIRADOR = 1

# Diccionario donde guardamos las celdas (botones)
tablero = {}


def demoColorChange():
    pass


# Create & Configure root
root = Tk()
Grid.rowconfigure(root, 0, weight=1)
Grid.columnconfigure(root, 0, weight=1)

# Frame principal
frame = Frame(root, bg="white")
frame.grid(row=0, column=0, sticky=N + S + E + W)

# Titulo (ROW 0)
titulo = Label(frame, text='Club de tir al plat - Les predreres', font=("Arial", 32), bg="white", padx=0, pady=10)
titulo.grid(sticky="W", row=0, columnspan=27)

# Serie (ROW 1)
serie = Label(frame, text=f'Serie: {SERIE}', font=("Arial", 14), bg="white")
serie.grid(sticky="W", row=1, columnspan=27)

# TIrador (ROW 2)
tirador = Label(frame, text=f'Tirador: {TIRADOR}', font=("Arial", 14), bg="white")
tirador.grid(sticky="W", row=2, columnspan=27)

# Cabecera del tablero (ROW 3)
for col_index in range(27):

    # Primera cabecera: Tirador
    if col_index == 0:
        btn = Button(frame, text="Tirador", bg="white", font=("Arial", 14, "bold"), borderwidth=1, command=demoColorChange)
        btn.grid(row=3, column=col_index, sticky=N + S + E + W)

    # Ultima cabecera: puntuacion total
    elif col_index == 26:
        btn = Button(frame, text="Total", bg="white", font=("Arial", 14, "bold"), borderwidth=1)
        btn.grid(row=3, column=col_index, sticky=N + S + E + W)

    # Cabeceras interiores: platos del 1 al 25
    else:
        btn = Button(frame, text=col_index, bg="white", font=("Arial", 14, "bold"), borderwidth=1)
        btn.grid(row=3, column=col_index, sticky=N + S + E + W)

# Tablero (ROW 4 EN ADELANTE)
for row_index in range(4, NUMERO_TIRADORES + 4):
    Grid.rowconfigure(frame, row_index, weight=1)

    for col_index in range(27):
        Grid.columnconfigure(frame, col_index, weight=1)

        # Primera columna: numero de tirador
        if col_index == 0:
            btn = Button(frame, text=row_index - 3, bg="white", font=("Arial", 14, "bold"), borderwidth=1)
            btn.grid(row=row_index, column=col_index, sticky=N + S + E + W)

            tablero[(row_index - 4, col_index)] = btn

        # Resto de columnas: platos
        else:
            btn = Button(frame, text=f"({col_index},{row_index-3})", bg="white", borderwidth=1)
            btn.grid(row=row_index, column=col_index, sticky=N + S + E + W)

            tablero[(row_index - 3, col_index)] = btn
    print(tablero.keys())

LOOP_ACTIVE = True
while LOOP_ACTIVE:
    root.update()
    USER_INPUT = input("Give me your command! Just type \"exit\" to close: ")
    if USER_INPUT == "exit":
        root.quit()
        LOOP_ACTIVE = False
    elif USER_INPUT == "next":

        TIRADOR += 1

        if TIRADOR > NUMERO_TIRADORES:
            TIRADOR = 1
            SERIE += 1

        tirador.configure(text=f"Tirador: {TIRADOR}")
        serie.configure(text=f"Serie: {SERIE}")

        if SERIE == 25:
            MessageBox.showinfo("Hola!", "Hola mundo")  # título, mensaje

    else:
        pass

