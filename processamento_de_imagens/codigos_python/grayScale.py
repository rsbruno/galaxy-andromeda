import cv2 as cv


def showImage(img):
    cv.imshow("Display", img)
    k = cv.waitKey(0)
    if k == ord("s"):
        cv.imwrite("saída.png", img)

if(__name__ == "__main__"):
    img = cv.imread("paisagem.jpg", cv.IMREAD_COLOR)

    height, width, chanels = img.shape

    for x in range(0, height):
        for y in range(0, width):
            ton = (img.item((x,y,0)) + img.item((x,y,1)) + img.item((x,y,2)))/3
            
            img.itemset((x,y,0),ton)
            #green
            img.itemset((x,y,1),ton)
            #red
            img.itemset((x,y,2),ton)
    #showImage(img)
    cv.imwrite("saida.png", img)


