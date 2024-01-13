from os.path import join,dirname,realpath
import pygame
import sys
import random
import os

pygame.init()

#zvuky
eat_sound = pygame.mixer.Sound("eat.wav")
over_sound = pygame.mixer.Sound("over.wav")

#cteni skore z textaku pokud existuje, jinak je best_score 0
if os.path.exists('best_score.txt'):
    with open(join(dirname(realpath(__file__)), "best_score.txt"), "r") as file:
            best_score = int(file.read())
else:
    best_score=0

#globalni promenne
WIDTH,HEIGHT = 600,600
BLOCK_SIZE = 50
RED = (255,0,0)
PINK = (222,69,143)
BLACK=(0,0,0)
WHITE = (255,255,255)
BLUE = (45, 126, 136)
GREEN = (45, 126, 34)

#promenne
game_over=False
new_press = True
main_menu=True
menu_skins= False
menu_fruit=False
score = 0
chosen_fruit= None
chosen_head= None
chosen_tail= None
chosen_color= None

screen = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Snake")
clock = pygame.time.Clock()


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

#funkce pro vykresleni textu na obrazovku
def drawText(text:str, font_str:str,font_size:int, text_color:str, x:int, y:int):
    #true da textu okraje a vypada to lepe pak
    font=pygame.font.SysFont(font_str, font_size)
    img = font.render(text, True, text_color)
    screen.blit(img,(x,y))

"""summary: trida pro veskera tlacitka, vytvori JEDEN ctverec s danymi parametry
    x -> x pozice tlacitka
    y -> y pozice tlacitka
"""  
class Button():     
    def __init__(self, x: int, y: int):
        self.color = WHITE
        self.width = 160
        self.height = 40
        self.x = x
        self.y = y
        self.rect = pygame.rect.Rect((self.x, self.y), (self.width, self.height)) 

    def draw(self):
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.width, self.height))

class Snake():
    #img1 je hlava, img2 je ocas
    def __init__(self, img1, img2, color):
        self.x,self.y = BLOCK_SIZE,BLOCK_SIZE
        self.x_dir = 1
        self.y_dir = 0
        self.head = pygame.Rect(self.x,self.y,BLOCK_SIZE,BLOCK_SIZE)
        self.body = [pygame.Rect(self.x-BLOCK_SIZE,self.y,BLOCK_SIZE,BLOCK_SIZE) for _ in range(2)]
        self.old_dir = "d"
        self.img_head = img1
        self.img_ocas = img2
        self.color = color

    def draw(self):
        #rotace hlavy
        #do prava
        if self.x_dir == 1 and self.y_dir==0:
            screen.blit(self.img_head, self.head)
        #dolu
        if self.x_dir == 0 and self.y_dir==1:
            screen.blit(pygame.transform.rotate(self.img_head,270), self.head)
        #do leva
        if self.x_dir == -1 and self.y_dir==0:
            screen.blit(pygame.transform.rotate(self.img_head,180), self.head)
        #nahoru
        if self.x_dir == 0 and self.y_dir==-1:
            screen.blit(pygame.transform.rotate(self.img_head,90), self.head)
            
        #kresleni tela
        for rect in self.body[1:]:
            pygame.draw.rect(screen, self.color, rect)
        
        #rotace ocasu
        #do prava
        if self.body[0].x +BLOCK_SIZE == self.body[1].x and self.body[0].y == self.body[1].y:
            screen.blit(self.img_ocas, self.body[0])
        #dolu
        if self.body[0].x == self.body[1].x and self.body[0].y+BLOCK_SIZE == self.body[1].y:
            screen.blit(pygame.transform.rotate(self.img_ocas,270), self.body[0])
        #do leva
        if self.body[0].x-BLOCK_SIZE == self.body[1].x and self.body[0].y == self.body[1].y:
            screen.blit(pygame.transform.rotate(self.img_ocas,180), self.body[0])
        #nahoru
        if self.body[0].x == self.body[1].x and self.body[0].y-BLOCK_SIZE == self.body[1].y:
            screen.blit(pygame.transform.rotate(self.img_ocas,90), self.body[0])
        

    def move(self):
        key = pygame.key.get_pressed()
        if key[pygame.K_w]:
            if self.old_dir != "s":
                self.y_dir = -1
                self.x_dir = 0
                self.old_dir="w"
        if key[pygame.K_a]:
            if self.old_dir != "d":
                self.y_dir = 0
                self.x_dir = -1
                self.old_dir="a"
        if key[pygame.K_d]:
            if self.old_dir != "a":
                self.y_dir = 0
                self.x_dir = 1
                self.old_dir="d"
        if key[pygame.K_s]:
            if self.old_dir != "w":
                self.y_dir = 1
                self.x_dir = 0
                self.old_dir="s"
        

    def update(self):
        self.body.append(self.head)
        for i in range(0,len(self.body)-1):
            self.body[i].x, self.body[i].y = self.body[i+1].x,self.body[i+1].y
        self.head.x += self.x_dir * BLOCK_SIZE
        self.head.y += self.y_dir * BLOCK_SIZE
        self.body.remove(self.head)

class Fruit():
    def __init__(self, img):

        #generuje ovoce na random pozice
        self.x = int(random.randint(0,WIDTH-BLOCK_SIZE)/BLOCK_SIZE)*BLOCK_SIZE
        self.y = int(random.randint(0,HEIGHT-BLOCK_SIZE)/BLOCK_SIZE)*BLOCK_SIZE
        self.img = img
        self.counter=0
        self.rand = random.choice([1, 2, 3, 4]) #pokud se ovoce hybe tak se vybere jedna ze 4 moznosti
        self.move = random.choice([True, False]) #generuje jestli se bude hybat nebo ne

        #pokud je ovoce na stejne pozici jako nejaka cast hada, vygeneruje se znova
        for rect in snake.body:
            while rect.x == self.x and rect.y == self.y or snake.head.x == self.x and snake.head.y == self.y:
                self.x = int(random.randint(0,WIDTH)/BLOCK_SIZE)*BLOCK_SIZE
                self.y = int(random.randint(0,HEIGHT)/BLOCK_SIZE)*BLOCK_SIZE
        self.rect = pygame.Rect(self.x,self.y,BLOCK_SIZE,BLOCK_SIZE)
        

    def update(self):
        #pokud se ovoce hybe
        if self.move:
            if self.counter <= 25:
                #do prava
                if self.rand == 1:
                    self.rect.x += 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.x >= 550:
                        self.counter = 0
                        self.rand = random.choice([2, 3, 4])
                    for rect in snake.body:
                        if fruit.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([2, 3, 4]) 
                #do leva
                if self.rand == 2:
                    self.rect.x -= 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.x <= 0:
                        self.counter = 0
                        self.rand = random.choice([1, 3, 4])
                    for rect in snake.body:
                        if fruit.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([1, 3, 4]) 
                #nahoru
                if self.rand == 3:
                    self.rect.y -= 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.y <= 0:
                        self.counter = 0
                        self.rand = random.choice([1, 2, 4])
                    for rect in snake.body:
                        if fruit.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([1, 2, 4]) 
                #dolu
                if self.rand == 4:
                    self.rect.y += 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.y >= 550:
                        self.counter = 0
                        self.rand = random.choice([1, 2, 3])
                    for rect in snake.body:
                        if fruit.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([1, 2, 3]) 
        #kdyz se ovoce nehybe tak se nic neudpdatuje
        else:
            pass
        
    #kresli ovoce
    def draw(self):
        screen.blit(self.img, self.rect)
        #pygame.draw.rect(screen,RED,self.rect)
    
#-------------------------main game loop-----------------------#
run = True

while run:
    
    clock.tick(10)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    #vytvori menu, zobrazi se pozadi a tlacitka s moznostmi pusteni hry a volby jake ovoce a skin chceme
    if main_menu == True:
        screen.blit(menu_sprite,(0,0))
        button1=Button(220, 330)
        button2=Button(220, 400)
        button3=Button(220, 470)
        drawText("MAIN MENU!!", "comicsans",50,PINK, 135, 80)
        if chosen_fruit:
            button1.draw()
            drawText("Play game", "comicsans", 25, PINK, 245, 330)
        button2.draw()
        button3.draw()
        
        drawText("Skin", "comicsans", 25, PINK, 270, 400)
        drawText("Fruit", "comicsans", 25, PINK, 270, 470)


        #kontroluje zmacknuti tlacitka pro spusteni hry
        if pygame.mouse.get_pressed()[0] and new_press:
            new_press = False
            if chosen_fruit and chosen_head and chosen_tail:
                if button1.rect.collidepoint(pygame.mouse.get_pos()):
                    main_menu=False
                    #kresli noveho hada a ovoce kazdou hru
                    snake=Snake(chosen_head, chosen_tail, chosen_color)
                    fruit = Fruit(chosen_fruit)
                    score=0

            if button2.rect.collidepoint(pygame.mouse.get_pos()):
                menu_skins=True
                main_menu=False

            if button3.rect.collidepoint(pygame.mouse.get_pos()):
                menu_fruit=True
                main_menu=False
            
        if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    elif menu_skins ==True:
        screen.blit(go_sprite,(0,0))
        drawText("CHOOSE A SKIN!!", "comicsans",50,WHITE, 80, 100)
        button1=Button(220, 275)
        button2=Button(220, 355)
        button3=Button(220, 435)
        button1.draw()
        button2.draw()
        button3.draw()
        screen.blit(pygame.transform.scale(head_sprite,(40,38)),(275,276))
        screen.blit(pygame.transform.scale(head2_sprite,(40,38)),(275,356))
        screen.blit(pygame.transform.scale(head3_sprite,(40,38)),(275,436))
        if pygame.mouse.get_pressed()[0] and new_press:
            new_press = False
            if button1.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_head= head_sprite
                chosen_tail= ocas_sprite
                chosen_color= PINK
                main_menu=True
                menu_skins=False
            if button2.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_head= head2_sprite
                chosen_tail= ocas2_sprite
                chosen_color= GREEN
                main_menu=True
                menu_skins=False
            if button3.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_head= head3_sprite
                chosen_tail= ocas3_sprite
                chosen_color= BLUE
                main_menu=True
                menu_skins=False
        if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    elif menu_fruit == True:
        screen.blit(go_sprite,(0,0))
        drawText("CHOOSE A FRUIT!!", "comicsans",50,WHITE, 70, 100)
        button1=Button(220, 275)
        button2=Button(220, 355)
        button3=Button(220, 435)
        button1.draw()
        button2.draw()
        button3.draw()
        screen.blit(pygame.transform.scale(jablko_sprite,(40,40)),(275,275))
        screen.blit(pygame.transform.scale(hruska_sprite,(40,40)),(275,355))
        screen.blit(pygame.transform.scale(svestka_sprite,(40,40)),(275,435))

        if pygame.mouse.get_pressed()[0] and new_press:
            new_press = False
            if button1.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_fruit= jablko_sprite
                main_menu=True
                menu_fruit=False
            if button2.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_fruit= hruska_sprite
                main_menu=True
                menu_fruit=False
            if button3.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_fruit= svestka_sprite
                main_menu=True
                menu_fruit=False
        if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    else:
        if game_over==False:
            screen.blit(bg_sprite,(0,0))
            snake.move()
            snake.update()
            fruit.update()

            #kreslici funkce
            fruit.draw()
            snake.draw()
            drawText(str(score), "comicsans",50, WHITE, int(WIDTH/2), int(0))
            
        
            #kolize s ovocem
            if snake.head.colliderect(fruit.rect):
                last_block = snake.body[-1]
                snake.body.append(pygame.Rect(last_block.x, last_block.y, BLOCK_SIZE, BLOCK_SIZE))
                #skore (musi byt and generovanim noveho ovoce)
                if fruit.move:
                    score += 2
                else:
                    score += 1
                fruit = Fruit(chosen_fruit)
                pygame.mixer.Sound.play(eat_sound)
                

            #kolize s telem
            for rect in snake.body:
                if snake.head.x == rect.x and snake.head.y == rect.y:
                    game_over=True
                    pygame.mixer.Sound.play(over_sound)
            

            #kolize out of screen
            if snake.head.x>=WIDTH or snake.head.x<0 or snake.head.y>=HEIGHT or snake.head.y<0:
                game_over=True
                pygame.mixer.Sound.play(over_sound)

        if game_over==True:
            screen.blit(go_sprite,(0,0))
            button1=Button(230, 330)
            button2=Button(230, 400)
            drawText("GAME OVER!!", "comicsans",50,WHITE, 150, 100)
            drawText("SCORE: "+str(score), "comicsans",36,WHITE, 230, 200)
            button1.draw()
            button2.draw()
            drawText("Main menu", "comicsans", 25, PINK, 245, 330)
            drawText("Play again", "comicsans", 25, PINK, 250, 400)
            #pokud je skore vetsi jak best skore, tak se v textaku prepise
            if score>best_score:
                best_score = score
                with open(join(dirname(realpath(__file__)), "best_score.txt"), "w") as file:
                    file.write(str(best_score))
            drawText("High score: " + str(best_score), "comicsans", 25, WHITE, 240, 250)

            if pygame.mouse.get_pressed()[0] and new_press:
                new_press = False
                if button2.rect.collidepoint(pygame.mouse.get_pos()):
                    game_over=False
                    score = 0
                    snake = Snake(chosen_head, chosen_tail, chosen_color)
                    fruit = Fruit(chosen_fruit)

                if button1.rect.collidepoint(pygame.mouse.get_pos()):
                    main_menu=True
                    menu_skins = False
                    menu_fruit=False
                    game_over=False

            if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    pygame.display.update()

pygame.quit()