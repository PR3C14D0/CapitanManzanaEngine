#version 330 core

in vec3 WorldPos;
out vec4 FragColor;

uniform vec3 cameraPos; // Pásale la posición de la cámara desde C++

void main() {
    // 1. Tamaño de cada celda y grosor de las líneas
    float gridSize = 1.0; 
    float thickness = 0.01; // Grosor de las líneas (0.03 = 3% de la celda)
    
    // Coordenadas locales de la celda actual (van de 0.0 a 1.0)
    vec2 coord = fract(WorldPos.xz / gridSize);

    // 2. Comprobar si estamos en el borde de la celda para pintar la línea
    // Si la coordenada está muy cerca de 0.0 o muy cerca de 1.0, es una línea
    float lineX = (coord.x < thickness || coord.x > 1.0 - thickness) ? 1.0 : 0.0;
    float lineZ = (coord.y < thickness || coord.y > 1.0 - thickness) ? 1.0 : 0.0;
    
    // Si es línea en X o en Z, pintamos
    float isLine = max(lineX, lineZ);
    
    // 3. Color base de la cuadrícula
    vec4 gridColor = vec4(0.8, 0.8, 0.8, isLine); // El Alpha es 1.0 en la línea y 0.0 en el hueco

    // 4. Efecto Fade (Obligatorio para que no se vea feo a lo lejos)
    float d = distance(cameraPos, WorldPos);
    // Smoothstep difumina suavemente. A 10.0 de distancia empieza a borrarse, a 60.0 desaparece.
    // (Ajusta estos valores según la escala de tu motor)
    float fade = 1.0 - smoothstep(10.0, 60.0, d);

    FragColor = vec4(gridColor.rgb, gridColor.a * fade);
    
    // Descartamos los píxeles vacíos para optimizar a tope
    if(FragColor.a < 0.01) {
        discard; 
    }
}