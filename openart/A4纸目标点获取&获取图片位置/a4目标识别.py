# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)

threshold=(181, 255)


sensor.set_auto_gain(True)          #自动增益
sensor.set_auto_whitebal(False)      #自动白平衡

sensor.skip_frames(time = 10)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.





while(True):
    clock.tick()                    # Update the FPS clock.

    img = sensor.snapshot().lens_corr(strength = 0.3, zoom = 1)         # Take a picture and return the image.

    img.get_statistics(roi=(0,0,10,20))
    #img.binary([threshold])

    #找矩形
    Rarea = [0,0,120,188]
    Points = img.find_rects(threshold = 20000)
    for r in Points:
        if r.w() > 100 and r.w() < 200 and r.h() > 50 and r.h() < 150 :
            print(r.corners()[0][0]-r.corners()[3][0])
            print(r.corners()[0][1]-r.corners()[1][1])
            if (r.corners()[0][1]-r.corners()[1][1])==0 and (r.corners()[0][0]-r.corners()[3][0])==0:
                img.draw_rectangle(r.rect(), color = (255, 0, 0))
                print(r.corners()[0])
                for p in r.corners(): img.draw_circle(p[0], p[1], 5, color = (0, 255, 0))
                area=[r[0],r[1],r[2],r[3]]
                img.draw_rectangle(area,123)
                #print(Points)  #[{"x":24, "y":12, "w":280, "h":191, "magnitude":235714}]
                print("--------------------")
                print(r)
                Xwidth = 35 / (r[2])
                Yheigt = 25 / (r[3])
                Xmiddle=r[0]+r[2]/2
                Ymiddle=r[1]+r[3]/2
                print("Middle:" ,Xmiddle,Ymiddle)
                #透视变换（未完成）


                #找黑点
                blobs = img.find_blobs([(0,200)],roi=area)

                for blob in blobs:
                    print(blob)
                    #img.draw_rectangle(blob[0:4],123)
                    img.draw_cross(blob[5], blob[6])
                    if (blob[4] <= 100):
                        print ("Find true blob : ",blob[0:2])
                        blobstrue = [(blob.cxf()-r[0])+3 ,r[3]-(blob.cyf()-r[1])+2]
                        coordinate = [round (blobstrue[0] * Xwidth) ,round (blobstrue[1] * Yheigt)]
                        #print (blobstrue)
                        img.draw_string(blob.x() - 5, blob.y() - 10, "(" + str(int(coordinate[0])) + "," + str(int(coordinate[1])) + ")", color = (0, 0, 255), scale = 1, mono_space = False)
                        print (coordinate)
                        #blobstrue[0]/Xwidth,blobstrue[1]/Yheigt
                        #输出点的坐标


#(69, 212)
#(181, 255)
