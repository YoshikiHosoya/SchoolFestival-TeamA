xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 294;
 50.00000;0.26151;50.00000;,
 -50.00000;0.26151;50.00000;,
 -50.00000;0.26151;-50.00000;,
 50.00000;0.26151;-50.00000;,
 -26.15005;40.51411;44.36260;,
 25.29094;40.51411;44.36260;,
 25.29094;40.51411;39.88746;,
 -26.15005;40.51411;39.88746;,
 44.36260;40.51411;24.12394;,
 44.36260;40.51411;-25.00960;,
 39.88746;40.51411;-25.00960;,
 39.88746;40.51411;24.12394;,
 26.10452;82.57894;46.77400;,
 26.10452;82.57894;44.36260;,
 24.97775;49.66463;44.76900;,
 25.36043;60.84412;44.36260;,
 24.97775;49.66463;39.88746;,
 25.36043;60.84412;39.88746;,
 47.97752;82.57894;24.90099;,
 45.92193;49.66463;23.82474;,
 44.36260;82.57894;24.90099;,
 39.88746;49.66463;23.82474;,
 44.36260;60.84412;24.19026;,
 39.88746;60.84412;24.19026;,
 25.36043;60.84412;44.36260;,
 -26.21953;60.84412;44.36260;,
 -26.21953;60.84412;39.88746;,
 25.36043;60.84412;39.88746;,
 44.36260;60.84412;-25.07601;,
 44.36260;60.84412;24.19026;,
 39.88746;60.84412;24.19026;,
 39.88746;60.84412;-25.07601;,
 47.90298;17.94408;-45.40328;,
 45.92193;49.66463;-43.56041;,
 45.92193;49.66463;-24.71040;,
 47.90298;17.94408;-25.74761;,
 -26.92268;17.94408;46.70127;,
 -25.83678;49.66463;44.76900;,
 -44.68679;49.66463;44.76900;,
 -46.57836;17.94408;46.70127;,
 -26.21953;60.84412;44.36260;,
 25.36043;60.84412;44.36260;,
 26.10452;82.57894;44.36260;,
 -26.96354;82.57894;44.36260;,
 44.36260;60.84412;24.19026;,
 44.36260;60.84412;-25.07601;,
 44.36260;82.57894;-25.78666;,
 44.36260;82.57894;24.90099;,
 45.71925;17.94408;-47.58702;,
 43.82776;49.66463;-45.65467;,
 -46.78103;49.66463;42.67474;,
 -48.76209;17.94408;44.51762;,
 25.36043;60.84412;39.88746;,
 -26.21953;60.84412;39.88746;,
 24.97775;49.66463;39.88746;,
 25.29094;40.51411;39.88746;,
 -26.15005;40.51411;39.88746;,
 -25.83678;49.66463;39.88746;,
 39.88746;60.84412;-25.07601;,
 39.88746;60.84412;24.19026;,
 39.88746;49.66463;-24.71040;,
 39.88746;40.51411;-25.00960;,
 39.88746;40.51411;24.12394;,
 39.88746;49.66463;23.82474;,
 50.00000;82.57894;50.00000;,
 50.00000;82.57894;-50.00000;,
 50.00000;100.26151;-50.00000;,
 50.00000;100.26151;50.00000;,
 50.00000;100.26151;50.00000;,
 -50.00000;100.26151;50.00000;,
 -50.00000;82.57894;50.00000;,
 50.00000;82.57894;50.00000;,
 26.06365;17.94408;-47.58702;,
 24.97775;49.66463;-45.65467;,
 -48.76209;17.94408;44.51762;,
 -46.78103;49.66463;42.67474;,
 -46.78103;49.66463;23.82474;,
 -48.76209;17.94408;24.86194;,
 47.90298;17.94408;-25.74761;,
 45.92193;49.66463;-24.71040;,
 44.36260;17.94408;-25.74761;,
 39.88746;49.66463;-24.71040;,
 44.36260;40.51411;-25.00960;,
 39.88746;40.51411;-25.00960;,
 -25.83678;49.66463;39.88746;,
 -25.83678;49.66463;44.76900;,
 -26.15005;40.51411;39.88746;,
 -26.15005;40.51411;44.36260;,
 -26.92268;17.94408;44.36260;,
 -26.92268;17.94408;46.70127;,
 47.97752;82.57894;-25.78666;,
 47.97752;82.57894;-45.47261;,
 -46.64958;82.57894;46.77400;,
 -26.96354;82.57894;46.77400;,
 50.00000;0.26151;-50.00000;,
 -50.00000;0.26151;-50.00000;,
 -50.00000;17.94408;-50.00000;,
 50.00000;17.94408;-50.00000;,
 -50.00000;0.26151;50.00000;,
 -50.00000;17.94408;50.00000;,
 45.79047;82.57894;-47.65975;,
 -48.83663;82.57894;44.58694;,
 -24.92866;40.51411;-44.36260;,
 25.29094;40.51411;-44.36260;,
 26.06365;17.94408;-44.36260;,
 -25.66461;17.94408;-44.36260;,
 -44.36260;17.94408;-25.74761;,
 -44.36260;17.94408;24.86194;,
 -44.36260;40.51411;24.12394;,
 -44.36260;40.51411;-25.00960;,
 26.10452;82.57894;-47.65975;,
 -48.83663;82.57894;24.90099;,
 -48.83663;82.57894;44.58694;,
 -24.92866;40.51411;-39.88746;,
 25.29094;40.51411;-39.88746;,
 25.29094;40.51411;-44.36260;,
 -24.92866;40.51411;-44.36260;,
 -44.36260;40.51411;-25.00960;,
 -44.36260;40.51411;24.12394;,
 -39.88746;40.51411;24.12394;,
 -39.88746;40.51411;-25.00960;,
 -50.00000;100.26151;-50.00000;,
 -24.99482;60.84412;-44.36260;,
 25.36043;60.84412;-44.36260;,
 25.36043;60.84412;-39.88746;,
 -24.99482;60.84412;-39.88746;,
 -39.88746;60.84412;-25.07601;,
 -39.88746;60.84412;24.19026;,
 -44.36260;60.84412;24.19026;,
 -44.36260;60.84412;-25.07601;,
 -45.32029;17.94408;-47.58702;,
 -43.48034;49.66463;-45.65467;,
 -24.63033;49.66463;-45.65467;,
 -25.66461;17.94408;-47.58702;,
 -47.50402;17.94408;-25.74761;,
 -45.57450;49.66463;-24.71040;,
 -45.57450;49.66463;-43.56041;,
 -47.50402;17.94408;-45.40328;,
 47.97752;82.57894;-25.78666;,
 44.36260;82.57894;-25.78666;,
 44.36260;60.84412;-25.07601;,
 39.88746;60.84412;-25.07601;,
 -25.70358;82.57894;-44.36260;,
 26.10452;82.57894;-44.36260;,
 25.36043;60.84412;-44.36260;,
 -24.99482;60.84412;-44.36260;,
 -44.36260;60.84412;-25.07601;,
 -44.36260;60.84412;24.19026;,
 -44.36260;82.57894;24.90099;,
 -44.36260;82.57894;-25.78666;,
 -26.21953;60.84412;39.88746;,
 -26.21953;60.84412;44.36260;,
 -26.96354;82.57894;44.36260;,
 -26.96354;82.57894;46.77400;,
 25.29094;40.51411;-39.88746;,
 24.97775;49.66463;-39.88746;,
 25.29094;40.51411;-44.36260;,
 26.06365;17.94408;-44.36260;,
 -39.88746;49.66463;23.82474;,
 -39.88746;40.51411;24.12394;,
 -44.36260;40.51411;24.12394;,
 -44.36260;17.94408;24.86194;,
 -50.00000;82.57894;-50.00000;,
 -50.00000;82.57894;50.00000;,
 -50.00000;100.26151;50.00000;,
 -25.70358;82.57894;-47.65975;,
 -45.38953;82.57894;-47.65975;,
 -47.57659;82.57894;-45.47261;,
 -47.57659;82.57894;-25.78666;,
 -46.45361;17.94408;-46.45361;,
 25.36043;60.84412;-39.88746;,
 25.36043;60.84412;-44.36260;,
 26.10452;82.57894;-44.36260;,
 -39.88746;60.84412;24.19026;,
 -44.36260;60.84412;24.19026;,
 -44.36260;82.57894;24.90099;,
 25.36043;60.84412;-39.88746;,
 24.97775;49.66463;-39.88746;,
 -24.99482;60.84412;-39.88746;,
 25.29094;40.51411;-39.88746;,
 -24.92866;40.51411;-39.88746;,
 -24.63033;49.66463;-39.88746;,
 -39.88746;60.84412;24.19026;,
 -39.88746;60.84412;-25.07601;,
 -39.88746;49.66463;23.82474;,
 -39.88746;40.51411;24.12394;,
 -39.88746;40.51411;-25.00960;,
 -39.88746;49.66463;-24.71040;,
 -25.66461;17.94408;-44.36260;,
 -24.63033;49.66463;-39.88746;,
 -24.92866;40.51411;-44.36260;,
 -24.92866;40.51411;-39.88746;,
 -39.88746;49.66463;-24.71040;,
 -45.57450;49.66463;-24.71040;,
 -39.88746;40.51411;-25.00960;,
 -44.36260;40.51411;-25.00960;,
 -44.36260;17.94408;-25.74761;,
 -47.50402;17.94408;-25.74761;,
 -46.52460;82.57894;-46.52460;,
 -25.70358;82.57894;-44.36260;,
 -24.99482;60.84412;-44.36260;,
 -24.99482;60.84412;-39.88746;,
 -39.88746;60.84412;-25.07601;,
 -44.36260;60.84412;-25.07601;,
 -44.36260;82.57894;-25.78666;,
 -47.57659;82.57894;-25.78666;,
 45.71925;17.94408;-47.58702;,
 26.06365;17.94408;-47.58702;,
 26.06365;17.94408;-44.36260;,
 -25.66461;17.94408;-44.36260;,
 -25.66461;17.94408;-47.58702;,
 -45.32029;17.94408;-47.58702;,
 -46.45361;17.94408;-46.45361;,
 47.90298;17.94408;-45.40328;,
 50.00000;17.94408;50.00000;,
 47.90298;17.94408;24.86194;,
 47.90298;17.94408;-25.74761;,
 44.36260;17.94408;-25.74761;,
 44.36260;17.94408;24.86194;,
 47.90298;17.94408;44.51762;,
 46.21030;17.94408;46.21030;,
 45.71925;17.94408;46.70127;,
 -50.00000;17.94408;50.00000;,
 26.06365;17.94408;46.70127;,
 26.06365;17.94408;44.36260;,
 -26.92268;17.94408;44.36260;,
 -26.92268;17.94408;46.70127;,
 -46.57836;17.94408;46.70127;,
 -44.36260;17.94408;24.86194;,
 -44.36260;17.94408;-25.74761;,
 -48.76209;17.94408;24.86194;,
 -47.50402;17.94408;-25.74761;,
 -47.50402;17.94408;-45.40328;,
 -48.76209;17.94408;44.51762;,
 46.28223;82.57894;46.28223;,
 47.97752;82.57894;44.58694;,
 50.00000;82.57894;-50.00000;,
 47.97752;82.57894;24.90099;,
 47.97752;82.57894;-25.78666;,
 44.36260;82.57894;24.90099;,
 44.36260;82.57894;-25.78666;,
 47.97752;82.57894;-45.47261;,
 45.79047;82.57894;-47.65975;,
 -50.00000;82.57894;-50.00000;,
 26.10452;82.57894;-47.65975;,
 26.10452;82.57894;-44.36260;,
 -25.70358;82.57894;-44.36260;,
 -25.70358;82.57894;-47.65975;,
 -45.38953;82.57894;-47.65975;,
 -46.52460;82.57894;-46.52460;,
 45.79047;82.57894;46.77400;,
 26.10452;82.57894;46.77400;,
 26.10452;82.57894;44.36260;,
 -26.96354;82.57894;44.36260;,
 -26.96354;82.57894;46.77400;,
 -46.64958;82.57894;46.77400;,
 -44.36260;82.57894;-25.78666;,
 -44.36260;82.57894;24.90099;,
 -47.57659;82.57894;-25.78666;,
 -48.83663;82.57894;24.90099;,
 -47.57659;82.57894;-45.47261;,
 -48.83663;82.57894;44.58694;,
 26.10452;82.57894;46.77400;,
 24.97775;49.66463;44.76900;,
 43.82776;49.66463;44.76900;,
 45.79047;82.57894;46.77400;,
 47.97752;82.57894;44.58694;,
 45.92193;49.66463;42.67474;,
 44.36260;40.51411;-25.00960;,
 44.36260;40.51411;24.12394;,
 44.36260;17.94408;24.86194;,
 44.36260;17.94408;-25.74761;,
 25.29094;40.51411;44.36260;,
 -26.15005;40.51411;44.36260;,
 -26.92268;17.94408;44.36260;,
 26.06365;17.94408;44.36260;,
 47.97752;82.57894;44.58694;,
 46.28223;82.57894;46.28223;,
 45.92193;49.66463;42.67474;,
 50.00000;0.26151;50.00000;,
 50.00000;17.94408;50.00000;,
 45.71925;17.94408;46.70127;,
 26.06365;17.94408;46.70127;,
 47.90298;17.94408;24.86194;,
 47.90298;17.94408;44.51762;,
 44.36260;17.94408;24.86194;,
 44.36260;40.51411;24.12394;,
 39.88746;40.51411;24.12394;,
 26.06365;17.94408;46.70127;,
 26.06365;17.94408;44.36260;,
 25.29094;40.51411;44.36260;,
 25.29094;40.51411;39.88746;,
 47.90298;17.94408;44.51762;,
 46.21030;17.94408;46.21030;;
 
 198;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 3;12,13,14;,
 3;13,15,14;,
 3;14,15,16;,
 3;15,17,16;,
 3;18,19,20;,
 3;19,21,22;,
 3;21,23,22;,
 3;22,20,19;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,33,32;,
 4;39,38,50,51;,
 3;52,53,54;,
 3;55,54,56;,
 3;54,53,57;,
 3;57,56,54;,
 3;58,59,60;,
 3;61,60,62;,
 3;60,59,63;,
 3;63,62,60;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,49,48;,
 4;74,75,76,77;,
 3;78,79,80;,
 3;79,81,82;,
 3;81,83,82;,
 3;82,80,79;,
 3;84,85,86;,
 3;86,85,87;,
 3;87,85,88;,
 3;85,89,88;,
 4;90,34,33,91;,
 4;92,38,37,93;,
 4;94,95,96,97;,
 4;95,98,99,96;,
 4;91,33,49,100;,
 4;101,50,38,92;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;100,49,73,110;,
 4;111,76,75,112;,
 4;113,114,115,116;,
 4;117,118,119,120;,
 4;66,121,69,68;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 3;138,139,79;,
 3;79,139,140;,
 3;79,140,81;,
 3;140,141,81;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 3;84,150,85;,
 3;150,151,85;,
 3;151,152,85;,
 3;152,153,85;,
 3;154,155,156;,
 3;155,73,156;,
 3;157,156,72;,
 3;156,73,72;,
 3;158,159,76;,
 3;159,160,76;,
 3;160,161,76;,
 3;161,77,76;,
 4;65,162,121,66;,
 4;162,163,164,121;,
 4;165,132,131,166;,
 4;167,136,135,168;,
 3;137,136,169;,
 3;169,136,130;,
 3;136,131,130;,
 3;170,171,155;,
 3;155,171,73;,
 3;172,110,171;,
 3;110,73,171;,
 3;158,76,173;,
 3;173,76,174;,
 3;175,174,111;,
 3;174,76,111;,
 3;176,177,178;,
 3;179,180,177;,
 3;177,180,181;,
 3;181,178,177;,
 3;182,183,184;,
 3;185,184,186;,
 3;184,183,187;,
 3;187,186,184;,
 3;133,132,188;,
 3;132,189,190;,
 3;189,191,190;,
 3;190,188,132;,
 3;192,193,194;,
 3;194,193,195;,
 3;196,195,197;,
 3;195,193,197;,
 3;167,198,136;,
 3;198,166,136;,
 3;166,131,136;,
 3;165,199,132;,
 3;132,199,200;,
 3;132,200,189;,
 3;200,201,189;,
 3;192,202,193;,
 3;202,203,193;,
 3;203,204,193;,
 3;204,205,193;,
 3;97,96,206;,
 3;206,96,207;,
 3;208,207,209;,
 3;207,96,210;,
 3;210,96,211;,
 3;96,212,211;,
 3;210,209,207;,
 3;206,213,97;,
 3;214,97,215;,
 3;97,213,216;,
 3;97,216,215;,
 3;216,217,215;,
 3;217,218,215;,
 3;214,215,219;,
 3;219,220,214;,
 3;214,220,221;,
 3;214,221,222;,
 3;221,223,222;,
 3;223,224,222;,
 3;224,225,226;,
 3;224,226,222;,
 3;226,227,222;,
 3;228,229,230;,
 3;229,231,230;,
 3;212,96,232;,
 3;227,233,222;,
 3;231,232,230;,
 3;232,96,230;,
 3;233,230,222;,
 3;230,96,222;,
 3;71,234,235;,
 3;236,71,235;,
 3;236,235,237;,
 3;236,237,238;,
 3;237,239,238;,
 3;239,240,238;,
 3;236,238,241;,
 3;236,241,242;,
 3;236,242,243;,
 3;242,244,243;,
 3;244,245,243;,
 3;245,246,247;,
 3;245,247,243;,
 3;247,248,243;,
 3;248,249,243;,
 3;71,70,250;,
 3;250,70,251;,
 3;252,251,253;,
 3;251,70,254;,
 3;254,70,255;,
 3;256,257,258;,
 3;257,259,258;,
 3;249,260,243;,
 3;255,70,261;,
 3;260,258,243;,
 3;258,259,243;,
 3;259,261,243;,
 3;261,70,243;,
 3;254,253,251;,
 3;250,234,71;,
 4;262,263,264,265;,
 4;266,267,19,18;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 3;276,277,278;,
 3;278,277,264;,
 3;277,265,264;,
 4;279,94,97,280;,
 4;214,222,1,0;,
 4;281,264,263,282;,
 4;283,19,267,284;,
 3;283,285,19;,
 3;19,285,286;,
 3;19,286,21;,
 3;286,287,21;,
 3;288,14,289;,
 3;289,14,290;,
 3;14,16,290;,
 3;16,291,290;,
 3;292,278,293;,
 3;293,278,281;,
 3;278,264,281;;
 
 MeshMaterialList {
  3;
  198;
  0,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  0,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  2,
  2,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1;;
  Material {
   0.345098;0.345098;0.345098;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game314\\Documents\\Visual Studio 2015\\Projects\\C++3D2nd\\data\\Texture\\field.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game314\\Documents\\Visual Studio 2015\\Projects\\C++3D2nd\\data\\Texture\\Marbl24l.jpg";
   }
  }
  Material {
   0.379608;0.379608;0.379608;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game314\\Documents\\Visual Studio 2015\\Projects\\C++3D2nd\\data\\Texture\\��.jpg";
   }
  }
 }
 MeshNormals {
  136;
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000002;0.000000;,
  -1.000000;0.000000;0.000057;,
  -0.999415;0.034213;0.000000;,
  -0.999415;0.034214;0.000064;,
  -0.999415;0.034212;0.000043;,
  -0.999415;0.034210;0.000000;,
  0.000006;0.000000;-1.000000;,
  0.000000;-0.000001;-1.000000;,
  0.000000;0.032679;-0.999466;,
  0.000010;0.032680;-0.999466;,
  0.000015;0.032682;-0.999466;,
  0.000000;0.032681;-0.999466;,
  0.921077;0.079667;-0.381143;,
  0.924015;0.000000;-0.382356;,
  1.000000;0.000000;0.000000;,
  0.998055;0.062332;0.000000;,
  0.000000;0.060803;0.998150;,
  0.000000;-0.000000;1.000000;,
  -0.382344;-0.000000;0.924020;,
  -0.381152;0.078842;0.921145;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.381160;0.078843;-0.921141;,
  0.382352;-0.000000;-0.924017;,
  -0.924012;0.000000;0.382364;,
  -0.921074;0.079668;0.381151;,
  0.000000;0.060805;-0.998150;,
  0.000000;-0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.998055;0.062332;0.000000;,
  0.000002;-0.032681;0.999466;,
  0.999415;-0.034213;-0.000035;,
  0.998056;-0.062331;-0.000000;,
  0.921079;-0.079667;-0.381139;,
  -0.381156;-0.078842;0.921143;,
  0.000000;-0.060803;0.998150;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.381164;-0.078843;-0.921139;,
  -0.921075;-0.079667;0.381147;,
  0.000000;-0.060805;-0.998150;,
  -0.998055;-0.062332;0.000000;,
  -0.503521;0.081603;-0.860121;,
  -0.382373;-0.000000;-0.924008;,
  0.000000;-0.000000;-1.000000;,
  0.000000;0.060805;-0.998150;,
  -0.998155;0.060716;0.000000;,
  -1.000000;0.000001;0.000000;,
  -0.827217;0.000000;-0.561882;,
  -0.921177;0.078181;-0.381209;,
  -1.000000;0.000002;0.000000;,
  0.000000;-0.000001;-1.000000;,
  -0.503520;-0.081603;-0.860121;,
  -0.921184;-0.078179;-0.381192;,
  -0.998155;-0.060715;0.000000;,
  -0.704620;0.083796;-0.704620;,
  -0.704632;-0.083795;-0.704608;,
  0.457272;-0.018374;0.889137;,
  0.842843;0.012972;0.538003;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.032681;0.999466;,
  -0.000007;0.000001;1.000000;,
  0.000000;0.000003;1.000000;,
  0.000002;-0.032680;0.999466;,
  -0.000000;-0.032680;0.999466;,
  1.000000;0.000001;0.000000;,
  1.000000;0.000000;-0.000029;,
  0.999415;-0.034215;-0.000000;,
  0.999415;-0.034214;-0.000035;,
  0.999415;-0.034213;-0.000000;,
  0.000000;0.032681;0.999466;,
  -0.000023;0.032680;0.999466;,
  -0.000015;0.032683;0.999466;,
  0.000000;0.032686;0.999466;,
  0.999414;0.034217;0.000000;,
  0.999415;0.034214;-0.000081;,
  0.999415;0.034212;-0.000081;,
  0.999415;0.034213;0.000000;,
  -0.999415;-0.034207;0.000000;,
  -0.999415;-0.034210;-0.000008;,
  -1.000000;0.000001;-0.000013;,
  -0.999414;-0.034216;0.000000;,
  -0.999415;-0.034214;-0.000017;,
  0.000000;-0.032680;-0.999466;,
  -0.000002;-0.004672;-0.999989;,
  -0.000002;-0.032681;-0.999466;,
  -0.000002;-0.032681;-0.999466;,
  0.000000;-0.032681;-0.999466;,
  -0.999415;0.034212;-0.000004;,
  -0.999415;0.034215;0.000000;,
  -0.999415;0.034214;-0.000009;,
  0.000000;0.032679;-0.999466;,
  -0.000003;0.032681;-0.999466;,
  0.000000;0.032683;-0.999466;,
  -0.000005;0.032682;-0.999466;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.999469;-0.032589;-0.000000;,
  1.000000;0.000001;-0.000013;,
  0.999469;-0.032589;-0.000016;,
  1.000000;0.000001;0.000000;,
  0.999469;-0.032587;-0.000011;,
  0.999469;-0.032585;-0.000000;,
  0.000000;0.000003;1.000000;,
  0.000008;0.004673;0.999989;,
  0.000000;-0.032680;0.999466;,
  -0.000001;-0.032681;0.999466;,
  0.000000;-0.032681;0.999466;,
  -0.000002;-0.032681;0.999466;,
  0.999469;0.032590;0.000000;,
  0.999469;0.032591;-0.000022;,
  0.999469;0.032589;-0.000014;,
  0.999469;0.032587;0.000000;,
  0.000030;0.032682;0.999466;,
  0.000030;0.032680;0.999466;,
  0.000000;0.032681;0.999466;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-0.060803;0.998150;,
  0.381155;-0.078841;0.921143;,
  0.921075;-0.079667;0.381148;,
  1.000000;0.000000;0.000000;,
  0.998056;-0.062331;-0.000000;,
  0.704557;-0.084932;0.704547;,
  0.503437;0.082416;0.860092;,
  0.000000;0.060803;0.998150;,
  0.998055;0.062332;0.000000;,
  0.921075;0.079668;0.381147;,
  0.000003;-0.032681;-0.999466;,
  0.000002;-0.032680;-0.999466;,
  -0.999415;-0.034213;0.000000;,
  -0.999415;-0.034215;0.000106;,
  -0.999415;-0.034210;0.000071;,
  0.704523;0.084937;0.704580;;
  198;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;4,5,3;,
  3;5,6,3;,
  3;3,6,2;,
  3;6,7,2;,
  3;13,8,12;,
  3;8,9,11;,
  3;9,10,11;,
  3;11,12,8;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;14,15,16,17;,
  4;18,19,20,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,25,15,14;,
  4;21,20,26,27;,
  3;61,22,22;,
  3;61,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;23,23,23;,
  3;62,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  4;23,23,23,23;,
  4;22,22,22,22;,
  4;28,29,25,24;,
  4;27,26,30,31;,
  3;63,64,32;,
  3;64,65,66;,
  3;65,67,66;,
  3;66,32,64;,
  3;68,69,70;,
  3;70,69,71;,
  3;71,69,33;,
  3;69,72,33;,
  4;34,16,15,35;,
  4;36,20,19,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;35,15,25,40;,
  4;41,26,20,36;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,25,29,42;,
  4;43,30,26,41;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;44,45,46,47;,
  4;48,49,50,51;,
  3;73,74,64;,
  3;64,74,75;,
  3;64,75,65;,
  3;75,76,65;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  3;68,77,69;,
  3;77,78,69;,
  3;78,79,69;,
  3;79,80,69;,
  3;81,52,82;,
  3;52,83,82;,
  3;84,82,85;,
  3;82,83,85;,
  3;53,86,87;,
  3;86,88,87;,
  3;88,89,87;,
  3;89,90,87;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;42,46,45,54;,
  4;55,50,49,56;,
  3;51,50,57;,
  3;57,50,44;,
  3;50,45,44;,
  3;7,91,52;,
  3;52,91,83;,
  3;92,93,91;,
  3;93,83,91;,
  3;53,87,94;,
  3;94,87,95;,
  3;96,95,97;,
  3;95,87,97;,
  3;38,38,38;,
  3;98,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;39,39,39;,
  3;99,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  3;100,101,102;,
  3;101,103,104;,
  3;103,105,104;,
  3;104,102,101;,
  3;106,107,108;,
  3;108,107,109;,
  3;110,109,111;,
  3;109,107,111;,
  3;55,58,50;,
  3;58,54,50;,
  3;54,45,50;,
  3;112,113,101;,
  3;101,113,114;,
  3;101,114,103;,
  3;114,115,103;,
  3;106,76,107;,
  3;76,116,107;,
  3;116,117,107;,
  3;117,118,107;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,119,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;120,19,59,121;,
  4;122,60,123,124;,
  4;23,23,23,23;,
  4;22,22,22,22;,
  3;122,125,60;,
  3;60,125,59;,
  3;125,121,59;,
  4;23,23,23,23;,
  4;22,22,22,22;,
  4;126,59,19,127;,
  4;128,123,60,129;,
  3;90,130,8;,
  3;8,130,131;,
  3;8,131,9;,
  3;131,86,9;,
  3;132,3,133;,
  3;133,3,134;,
  3;3,2,134;,
  3;2,81,134;,
  3;129,60,135;,
  3;135,60,126;,
  3;60,59,126;;
 }
 MeshTextureCoords {
  294;
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.556862;0.778536;,
  0.445006;0.778536;,
  0.445006;0.788267;,
  0.556862;0.788267;,
  0.403536;0.822544;,
  0.403536;0.929382;,
  0.413267;0.929382;,
  0.413267;0.822544;,
  0.875000;0.243077;,
  0.847350;0.243077;,
  0.875000;0.125000;,
  0.862257;0.165106;,
  0.816732;0.125000;,
  0.809701;0.165106;,
  0.375000;0.243077;,
  0.375000;0.125000;,
  0.416404;0.243077;,
  0.447030;0.125000;,
  0.401469;0.165106;,
  0.454063;0.165106;,
  0.444855;0.471464;,
  0.557013;0.471464;,
  0.557013;0.461733;,
  0.444855;0.461733;,
  0.403536;0.320474;,
  0.403536;0.427600;,
  0.413267;0.427600;,
  0.413267;0.320474;,
  0.350002;0.011205;,
  0.350002;0.125000;,
  0.125000;0.125000;,
  0.125000;0.011205;,
  0.375000;0.738795;,
  0.375000;0.625000;,
  0.600003;0.625000;,
  0.600003;0.738795;,
  0.573878;0.595716;,
  0.428542;0.595716;,
  0.426446;0.529963;,
  0.575975;0.529963;,
  0.181839;0.154284;,
  0.320656;0.154284;,
  0.322659;0.220037;,
  0.179837;0.220037;,
  0.399997;0.011205;,
  0.399997;0.125000;,
  0.625000;0.625000;,
  0.625000;0.761552;,
  0.420525;0.590210;,
  0.582167;0.590210;,
  0.421724;0.644317;,
  0.420743;0.688604;,
  0.581949;0.688604;,
  0.580968;0.644317;,
  0.328584;0.159790;,
  0.174192;0.159790;,
  0.327438;0.105683;,
  0.328376;0.061396;,
  0.174400;0.061396;,
  0.175338;0.105683;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.125000;0.250000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;0.011205;,
  0.625000;0.125000;,
  0.850003;0.011205;,
  0.850003;0.125000;,
  0.625000;0.125000;,
  0.625000;0.011205;,
  0.375000;0.738795;,
  0.375000;0.625000;,
  0.415632;0.738795;,
  0.447030;0.625000;,
  0.400032;0.657827;,
  0.452766;0.657827;,
  0.183268;0.125000;,
  0.125000;0.125000;,
  0.188999;0.092173;,
  0.136315;0.092173;,
  0.151871;0.011205;,
  0.125000;0.011205;,
  0.125000;0.243077;,
  0.350002;0.243077;,
  0.600003;0.506923;,
  0.375000;0.506923;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.399997;0.243077;,
  0.625000;0.483309;,
  0.570241;0.092782;,
  0.428738;0.092782;,
  0.426561;0.024502;,
  0.572315;0.024502;,
  0.677451;0.024502;,
  0.820053;0.024502;,
  0.817974;0.092782;,
  0.679531;0.092782;,
  0.625000;0.243077;,
  0.625000;0.243077;,
  0.850003;0.243077;,
  0.554206;0.961733;,
  0.445006;0.961733;,
  0.445006;0.971464;,
  0.554206;0.971464;,
  0.596464;0.929382;,
  0.596464;0.822544;,
  0.586733;0.822544;,
  0.586733;0.929382;,
  0.625000;0.250000;,
  0.554350;0.278536;,
  0.444855;0.278536;,
  0.444855;0.288267;,
  0.554350;0.288267;,
  0.586733;0.320474;,
  0.586733;0.427600;,
  0.596464;0.427600;,
  0.596464;0.320474;,
  0.600003;0.011205;,
  0.600003;0.125000;,
  0.375000;0.125000;,
  0.375000;0.011205;,
  0.875000;0.011205;,
  0.875000;0.125000;,
  0.649997;0.125000;,
  0.649997;0.011205;,
  0.375000;0.506923;,
  0.416404;0.506923;,
  0.401469;0.584894;,
  0.454063;0.584894;,
  0.572425;0.220037;,
  0.426446;0.220037;,
  0.428542;0.154284;,
  0.570428;0.154284;,
  0.679344;0.154284;,
  0.818161;0.154284;,
  0.820163;0.220037;,
  0.677341;0.220037;,
  0.190299;0.165106;,
  0.137743;0.165106;,
  0.152650;0.243077;,
  0.125000;0.243077;,
  0.699448;0.092173;,
  0.693840;0.125000;,
  0.646724;0.092173;,
  0.662015;0.011205;,
  0.542715;0.125000;,
  0.537093;0.092173;,
  0.589860;0.092173;,
  0.574539;0.011205;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.375000;0.243077;,
  0.600003;0.243077;,
  0.649997;0.243077;,
  0.875000;0.243077;,
  0.625952;0.011205;,
  0.700717;0.165106;,
  0.648132;0.165106;,
  0.662773;0.243077;,
  0.535827;0.165106;,
  0.588446;0.165106;,
  0.573784;0.243077;,
  0.420525;0.159790;,
  0.421724;0.105683;,
  0.578329;0.159790;,
  0.420743;0.061396;,
  0.578122;0.061396;,
  0.577187;0.105683;,
  0.825808;0.159790;,
  0.671417;0.159790;,
  0.824662;0.105683;,
  0.825600;0.061396;,
  0.671624;0.061396;,
  0.672562;0.105683;,
  0.337985;0.011205;,
  0.306160;0.125000;,
  0.353276;0.092173;,
  0.300553;0.092173;,
  0.557117;0.625000;,
  0.625000;0.625000;,
  0.551508;0.657827;,
  0.604228;0.657827;,
  0.588935;0.738795;,
  0.625000;0.738795;,
  0.625951;0.243077;,
  0.337227;0.243077;,
  0.351868;0.165106;,
  0.299283;0.165106;,
  0.550237;0.584894;,
  0.602820;0.584894;,
  0.588176;0.506923;,
  0.625000;0.506923;,
  0.385702;0.256032;,
  0.434841;0.256032;,
  0.434841;0.264093;,
  0.564162;0.264093;,
  0.564162;0.256032;,
  0.613301;0.256032;,
  0.616134;0.258866;,
  0.380242;0.261492;,
  0.375000;0.500000;,
  0.380242;0.437155;,
  0.380242;0.310631;,
  0.389093;0.310631;,
  0.389093;0.437155;,
  0.380242;0.486294;,
  0.384474;0.490526;,
  0.385702;0.491753;,
  0.625000;0.500000;,
  0.434841;0.491753;,
  0.434841;0.485907;,
  0.567307;0.485907;,
  0.567307;0.491753;,
  0.616446;0.491753;,
  0.610907;0.437155;,
  0.610907;0.310631;,
  0.621905;0.437155;,
  0.618760;0.310631;,
  0.618760;0.261492;,
  0.621905;0.486294;,
  0.384294;0.759294;,
  0.380056;0.763533;,
  0.375000;1.000000;,
  0.380056;0.812748;,
  0.380056;0.939467;,
  0.389093;0.812748;,
  0.389093;0.939467;,
  0.380056;0.988682;,
  0.385524;0.994149;,
  0.625000;1.000000;,
  0.434739;0.994149;,
  0.434739;0.985907;,
  0.564259;0.985907;,
  0.564259;0.994149;,
  0.613474;0.994149;,
  0.616312;0.991312;,
  0.385524;0.758065;,
  0.434739;0.758065;,
  0.434739;0.764093;,
  0.567409;0.764093;,
  0.567409;0.758065;,
  0.616624;0.758065;,
  0.610907;0.939467;,
  0.610907;0.812748;,
  0.618942;0.939467;,
  0.622092;0.812748;,
  0.618942;0.988682;,
  0.622092;0.763533;,
  0.625000;0.506923;,
  0.625000;0.625000;,
  0.399997;0.625000;,
  0.399997;0.506923;,
  0.149997;0.243077;,
  0.149997;0.125000;,
  0.320469;0.092782;,
  0.182026;0.092782;,
  0.179947;0.024502;,
  0.322549;0.024502;,
  0.428738;0.657218;,
  0.573683;0.657218;,
  0.575860;0.725498;,
  0.426561;0.725498;,
  0.375000;0.483309;,
  0.394376;0.501629;,
  0.375000;0.625000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.399997;0.738795;,
  0.625000;0.738795;,
  0.375000;0.011205;,
  0.149997;0.011205;,
  0.415632;0.011205;,
  0.400032;0.092173;,
  0.452766;0.092173;,
  0.875000;0.011205;,
  0.848129;0.011205;,
  0.863685;0.092173;,
  0.811001;0.092173;,
  0.375000;0.761552;,
  0.394376;0.743906;;
 }
}
