# A test script to visualize the function which is converting from wavelength to visible spectrum in rgb

import pygame
from pygame.locals import *

pygame.init()

root = pygame.display.set_mode((1000, 400), pygame.RESIZABLE)
root.fill((0,0,0))

def visSpec(w):
    if w >= 380 and w < 440:
        R = -(w - 440.) / (440. - 380.)
        G = 0.0
        B = 1.0
    elif w >= 440 and w < 490:
        R = 0.0
        G = (w - 440.) / (490. - 440.)
        B = 1.0
    elif w >= 490 and w < 510:
        R = 0.0
        G = 1.0
        B = -(w - 510.) / (510. - 490.)
    elif w >= 510 and w < 580:
        R = (w - 510.) / (580. - 510.)
        G = 1.0
        B = 0.0
    elif w >= 580 and w < 645:
        R = 1.0
        G = -(w - 645.) / (645. - 580.)
        B = 0.0
    elif w >= 645 and w <= 780:
        R = 1.0
        G = 0.0
        B = 0.0
    elif w >= 780 and w <= 840:
        R = 1.0
        G = 0.0
        B = (w - 780.) / (840. - 780.)
    else:
        R = 0.0
        G = 0.0
        B = 0.0
    return (R*255, G*255, B*255)

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    for x in range(380, 1000):
        pygame.draw.circle(root, visSpec(x), (2*(x - 380), 250), 2)

        pygame.draw.circle(root, (255,0,0), (2*(x - 380), 200+150*-(visSpec(x)[0]/255)), 2)
        pygame.draw.circle(root, (0,255,0), (2*(x - 380), 200+150*-(visSpec(x)[1]/255)), 2)
        pygame.draw.circle(root, (0,0,255), (2*(x - 380), 200+150*-(visSpec(x)[2]/255)), 2)

    pygame.display.flip()
    root.fill((100,100,100))

pygame.quit()