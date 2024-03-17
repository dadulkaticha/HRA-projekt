import pygame
from os.path import join, dirname, realpath

pygame.init()

#globalni promenne
WIDTH,HEIGHT = 600,600
BLOCK_SIZE = 50
WHITE = (255,255,255)
RED = (255,0,0)
PINK = (222,69,143)
BLACK=(0,0,0)
BLUE = (45, 126, 136)
GREEN = (45, 126, 34)

#promenne
game_over=False
new_press = True
main_menu=True
menu_skins= False
menu_fruit=False
menu_difficulty=False
score = 0
chosen_fruit= None
chosen_head= None
chosen_tail= None
chosen_color= None
chosen_difficulty= None

screen = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Snake")
clock = pygame.time.Clock()

#zvuky
eat_sound = pygame.mixer.Sound("eat.wav")
over_sound = pygame.mixer.Sound("over.wav")

#sprity
head_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/head.png")).convert_alpha()
hruska_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/hruska.png")).convert_alpha()
svestka_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/svestka.png")).convert_alpha()
jablko_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/jablko.png")).convert_alpha()
ocas_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/ocas.png")).convert_alpha()
bg_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/bg.png")).convert_alpha()
menu_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/menu.png")).convert_alpha()
go_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/go.png")).convert_alpha()
head2_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/hlava2.png")).convert_alpha()
ocas2_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/ocasek2.png")).convert_alpha()
head3_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/hlava3.png")).convert_alpha()
ocas3_sprite = pygame.image.load(join(dirname(realpath(__file__)), "obrazky/ocasek3.png")).convert_alpha()