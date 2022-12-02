from tkinter import *
from tkinter import messagebox as MessageBox

NUMERO_TIRADORES = 1
SERIE = 1
TIRADOR = 1


def next():
    global TIRADOR
    global SERIE

    TIRADOR += 1

    if TIRADOR > NUMERO_TIRADORES:
        TIRADOR = 1
        SERIE += 1

    if TIRADOR == NUMERO_TIRADORES and SERIE == 25:
        MessageBox.showinfo("Hola!", "Hola mundo")  # título, mensaje


# Diccionario donde guardamos las celdas (botones)
tablero = {}

# Diccionario donde guardamos el boton que indica el tocal de platos
puntuaciones_tiradores = [0, 0, 0, 0, 0, 0]
total = {}

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

# Tirador (ROW 2)
tirador = Label(frame, text=f'Tirador: {TIRADOR}', font=("Arial", 14), bg="white")
tirador.grid(sticky="W", row=2, columnspan=27)

# Cabecera del tablero (ROW 3)
for col_index in range(27):

    # Primera cabecera: Tirador
    if col_index == 0:
        btn = Button(frame, text="Tirador", bg="white", font=("Arial", 14, "bold"), borderwidth=1)
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

        # Resto de columnas: platos
        elif 0 < col_index <= 25:
            btn = Button(frame, text=f"({row_index - 3},{col_index})", bg="white", borderwidth=1)
            btn.grid(row=row_index, column=col_index, sticky=N + S + E + W)
            tablero[(row_index - 3, col_index)] = btn

        else:
            btn = Button(frame, text=f"{puntuaciones_tiradores[row_index - 3]}", bg="white", borderwidth=1)
            btn.grid(row=row_index, column=col_index, sticky=N + S + E + W)
            total[row_index - 3] = btn

    print(tablero.keys())
    print(total)

LOOP_ACTIVE = True
while LOOP_ACTIVE:
    root.update()

    tirador.configure(text=f"Tirador: {TIRADOR}")
    serie.configure(text=f"Serie: {SERIE}")

    print(f"Tirador: {TIRADOR}    Serie: {SERIE}")
    USER_INPUT = input("Give me your command! ")

    if USER_INPUT == "exit":
        root.quit()
        LOOP_ACTIVE = False

    elif USER_INPUT == "tocado":
        # ponemos el cuadro en verde
        tablero.get((TIRADOR, SERIE)).configure(bg="green")
        # sumamos un punto al tirador
        puntuaciones_tiradores[TIRADOR] += 1
        # cambiamos el total en pantalla
        total.get(TIRADOR).configure(text=f"{puntuaciones_tiradores[TIRADOR]}")
        #siguiente tirador
        next()

    elif USER_INPUT == "fallo":
        # ponemos el cuadro en verde
        tablero.get((TIRADOR, SERIE)).configure(bg="red")
        # sumamos un punto al tirador
        total.get(TIRADOR).configure(text=f"{puntuaciones_tiradores[TIRADOR]}")
        #siguiente tirador
        next()


    else:
        pass
