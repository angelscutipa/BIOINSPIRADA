import csv
import sys

movimientos = {}
premios = {}

desc = 0.9

err = 0.001

def leer_en():
    with open('movimi2.csv', 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for fila in reader:
            if fila[0] in movimientos:
                if fila[1] in movimientos[fila[0]]:
                    movimientos[fila[0]][fila[1]].append((float(fila[3]), fila[2]))
                else:
                    movimientos[fila[0]][fila[1]] = [(float(fila[3]), fila[2])]
            else:
                movimientos[fila[0]] = {fila[1]:[(float(fila[3]),fila[2])]}

    with open('premios.csv', 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for fila in reader:
            premios[fila[0]] = float(fila[1]) if fila[1] != 'None' else None

leer_en()

"""for key in movimientos:
  print key, ":", movimientos[key]
  print

for key in premios:
  print key, ":", premios[key]
  print"""

class MDP:
    def __init__(self, transicion={}, premio={}, desc=.9):
        self.estados = transicion.keys()
        self.transicion = transicion
        self.premio = premio
        self.desc = desc

    def R(self, estado):
        return self.premio[estado]

    def acciones(self, estado):
        return self.transicion[estado].keys()

    def T(self, estado, accion):
        return self.transicion[estado][accion]

mdp = MDP(transicion=movimientos, premio=premios)

def valor_i(): 
    estados = mdp.estados
    acciones = mdp.acciones
    T = mdp.T
    R = mdp.R

    V1 = {s: 0 for s in estados}
    while True:
        V = V1.copy()
        delta = 0
        for s in estados:
            #Bellman
            V1[s] = R(s) + desc * max([ sum([p * V[s1] for (p, s1) in T(s, a)]) for a in acciones(s)])
            #valor
            delta = max(delta, abs(V1[s] - V[s]))

        if delta < err * (1 - desc) / desc:
            return V


def mejor_politica(V):

    estados = mdp.estados
    acciones = mdp.acciones
    pi = {}
    for s in estados:
        pi[s] = max(acciones(s), key=lambda a: utilidad_esperada(a, s, V))
    return pi


def utilidad_esperada(a, s, V):
    T = mdp.T
    return sum([p * V[s1] for (p, s1) in mdp.T(s, a)])


V = valor_i()
print 'estado - valor'
for s in V:
    print s, ' - ' , V[s]
pi = mejor_politica(V)
print '\nes una politica optima \nestado - accion'
for s in pi:
    print s, ' - ' , pi[s]
