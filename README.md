<h3>Maxence Retier</h3>
<h1>----------ParallaxMapping----------</h1>

## **Overall Summary**

- [Description](#Description-of-the-project:)  
- [Interface description](#Interface-description)  
- [Control](#Control)  
- [Work in progress](#Work-in-progress)  


## **Description of the project:**
<p> I discovered parallax mapping by playing different video games. I got very interested in the subject to understand why it was used and how it worked. I then created a mini OpengGL engine to perform parallax mapping. </p>

## **Interface description :**
<p> You have at your disposal a window from the ImGui library, which will allow you to move, to move the object, and to change the heightscale of the parallax mapping.</p>

## **Control:**
<p>Control the camera with the mouse. You can also progress in the world. To move in the scene you can do a right click on the window. This gonna capture your mouse, and you are gonna controle the camera with your mouse (do an another right click to uncapture your mouse).
With the Z, S, Q and D on your keyboard you can move all around the object.<br> </p>

 controle      |     signification 
 ------------- | -------------   
 Z             |   moving forward  
 Q             |   moving left     
 S             |   moving back    
 D             |   moving right 
 Space         |   Go Up 
 Ctrl Right    |   Go Down 
 Right click   |   Enter/Exit the frameBuffer
 Scape         |   Exit the program

## **What I do in the project ?**
<ol>
    <li>Draw a square with vertices</li>
    <li>Parse an Obj</li>
    <li>Display the Obj in 2D</li>
    <li>Load a texture, with the library stb_image</li>
    <li>Create different type of light</li>
    <ul> • Ambient light </ul>
    <ul> • Diffuse light </ul>
    <ul> • Specular light </ul>
    <ul> • Spot light </ul>
    <ul> • Smooth light </ul>
    <li>implementation of the ImGui library</li>
    <li>Transform the proportion of the model</li>
    <ul> • scale </ul>
    <ul> • translate </ul>
    <ul> • RotateXYZ </ul>
    <li>Setting up the dephTest</li>
    <li>Setting up the BackFace Culling</li>
    <li>Parsing of the .mtl</li>   
</ol>

## **Work in progress**
<p>I would then like to develop a shader doing interior mapping. (False room) which takes up some of the principles of parallax mapping.</p>

## **References:**

https://learnopengl.com/