import pygame
from assets import screen

"""
    summary: funkce pro vykresleni textu na obrazovku
    text -> text ktery se ma vykreslit
    font_str -> font textu
    font_size -> velikost textu
    text_color -> barva textu
    x -> x pozice textu
    y -> y pozice textu
"""
def drawText(text:str, font_str:str,font_size:int, text_color:str, x:int, y:int):
    #true da textu okraje a vypada to lepe pak
    font=pygame.font.SysFont(font_str, font_size)
    img = font.render(text, True, text_color)
    screen.blit(img,(x,y))