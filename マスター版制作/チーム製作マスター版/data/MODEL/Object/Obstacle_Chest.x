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
 302;
 20.59202;15.63669;9.70007;,
 24.99670;15.63669;9.70007;,
 24.99670;17.69393;5.18325;,
 20.59202;17.69393;5.18325;,
 24.99670;18.51711;0.58332;,
 20.59202;18.51711;0.58332;,
 20.59202;-18.75709;9.70007;,
 20.59202;-18.75709;5.18325;,
 24.99670;-18.75709;5.18325;,
 24.99670;-18.75709;9.70007;,
 20.59202;-18.75709;0.58332;,
 24.99670;-18.75709;0.58332;,
 24.99670;17.66411;-3.71976;,
 20.59202;17.66411;-3.71976;,
 24.99670;15.63669;-7.77368;,
 20.59202;15.63669;-7.77368;,
 20.59202;-18.75709;-3.71976;,
 24.99670;-18.75709;-3.71976;,
 20.59202;-18.75709;-7.77368;,
 24.99670;-18.75709;-7.77368;,
 20.59202;5.22172;-16.52717;,
 20.59202;13.03783;-12.32602;,
 24.99670;13.03783;-12.32602;,
 24.99670;5.22172;-16.52717;,
 20.59202;-18.75709;-16.52717;,
 24.99670;-18.75709;-16.52717;,
 24.99670;-18.75709;-12.32602;,
 20.59202;-18.75709;-12.32602;,
 20.59202;5.22172;17.69379;,
 24.99670;5.22172;17.69379;,
 24.99670;13.18681;13.64108;,
 20.59202;13.18681;13.64108;,
 20.59202;-18.75709;17.69379;,
 20.59202;-18.75709;13.64108;,
 24.99670;-18.75709;13.64108;,
 24.99670;-18.75709;17.69379;,
 -20.69543;17.69393;5.18325;,
 -24.99670;17.69393;5.18325;,
 -24.99670;15.63669;9.70007;,
 -20.69543;15.63669;9.70007;,
 -20.69543;18.51711;0.58332;,
 -24.99670;18.51711;0.58332;,
 -20.69543;-18.75709;9.70007;,
 -24.99670;-18.75709;9.70007;,
 -24.99670;-18.75709;5.18325;,
 -20.69543;-18.75709;5.18325;,
 -24.99670;-18.75709;0.58332;,
 -20.69543;-18.75709;0.58332;,
 -20.69543;17.66411;-3.71976;,
 -24.99670;17.66411;-3.71976;,
 -20.69543;15.63669;-7.77368;,
 -24.99670;15.63669;-7.77368;,
 -24.99670;-18.75709;-3.71976;,
 -20.69543;-18.75709;-3.71976;,
 -24.99670;-18.75709;-7.77368;,
 -20.69543;-18.75709;-7.77368;,
 -20.69543;5.22172;-16.52717;,
 -24.99670;5.22172;-16.52717;,
 -24.99670;13.03783;-12.32602;,
 -20.69543;13.03783;-12.32602;,
 -20.69543;-18.75709;-12.32602;,
 -24.99670;-18.75709;-12.32602;,
 -24.99670;-18.75709;-16.52717;,
 -20.69543;-18.75709;-16.52717;,
 -20.69543;13.18681;13.64108;,
 -24.99670;13.18681;13.64108;,
 -24.99670;5.22172;17.69379;,
 -20.69543;5.22172;17.69379;,
 -20.69543;-18.75709;17.69379;,
 -24.99670;-18.75709;17.69379;,
 -24.99670;-18.75709;13.64108;,
 -20.69543;-18.75709;13.64108;,
 24.99670;-2.02942;9.70007;,
 24.99670;-18.75709;9.70007;,
 24.99670;-18.75709;5.18325;,
 24.99670;-2.02942;5.18325;,
 24.99670;-18.75709;0.58332;,
 24.99670;-2.02942;0.58332;,
 -24.99670;-2.02942;9.70007;,
 -24.99670;-2.02942;5.18325;,
 -24.99670;-18.75709;5.18325;,
 -24.99670;-18.75709;9.70007;,
 -24.99670;-2.02942;0.58332;,
 -24.99670;-18.75709;0.58332;,
 24.99670;-18.75709;-3.71976;,
 24.99670;-2.02942;-3.71976;,
 24.99670;-18.75709;-7.77368;,
 24.99670;-2.02942;-7.77368;,
 -24.99670;-2.02942;-3.71976;,
 -24.99670;-18.75709;-3.71976;,
 -24.99670;-2.02942;-7.77368;,
 -24.99670;-18.75709;-7.77368;,
 24.99670;-2.02942;-16.52717;,
 24.99670;-2.02942;-12.32602;,
 24.99670;-18.75709;-12.32602;,
 24.99670;-18.75709;-16.52717;,
 -24.99670;-2.02942;-16.52717;,
 -24.99670;-18.75709;-16.52717;,
 -24.99670;-18.75709;-12.32602;,
 -24.99670;-2.02942;-12.32602;,
 24.99670;-2.02942;17.69379;,
 24.99670;-18.75709;13.64108;,
 24.99670;-2.02942;13.64108;,
 -24.99670;-2.02942;17.69379;,
 -24.99670;-2.02942;13.64108;,
 -24.99670;-18.75709;13.64108;,
 24.99670;-2.02942;-16.52717;,
 24.99670;-18.75709;-16.52717;,
 20.59202;-18.75709;-16.52717;,
 20.59202;-2.02942;-16.52717;,
 20.59202;-2.02942;17.69379;,
 20.59202;-18.75709;17.69379;,
 24.99670;-18.75709;17.69379;,
 24.99670;-2.02942;17.69379;,
 -24.99670;-2.02942;-16.52717;,
 -20.69543;-2.02942;-16.52717;,
 -20.69543;-18.75709;-16.52717;,
 -24.99670;-18.75709;-16.52717;,
 -24.99670;-2.02942;17.69379;,
 -24.99670;-18.75709;17.69379;,
 -20.69543;-18.75709;17.69379;,
 -20.69543;-2.02942;17.69379;,
 -15.71286;15.63669;9.70007;,
 -15.71286;17.69393;5.18325;,
 -15.71286;18.51711;0.58332;,
 -15.71286;-18.75709;5.18325;,
 -15.71286;-18.75709;9.70007;,
 -15.71286;-18.75709;0.58332;,
 -15.71286;17.66411;-3.71976;,
 -15.71286;15.63669;-7.77368;,
 -15.71286;-18.75709;-3.71976;,
 -15.71286;-18.75709;-7.77368;,
 -15.71286;13.03783;-12.32602;,
 -15.71286;5.22172;-16.52717;,
 -15.71286;-18.75709;-16.52717;,
 -15.71286;-18.75709;-12.32602;,
 -15.71286;5.22172;17.69379;,
 -15.71286;13.18681;13.64108;,
 -15.71286;-18.75709;13.64108;,
 -15.71286;-18.75709;17.69379;,
 -15.71286;-2.02942;-16.52717;,
 -15.71286;-18.75709;-16.52717;,
 -15.71286;-18.75709;17.69379;,
 -15.71286;-2.02942;17.69379;,
 -11.06100;15.63669;9.70007;,
 -11.06100;17.69393;5.18325;,
 -11.06100;18.51711;0.58332;,
 -11.06100;-18.75709;5.18325;,
 -11.06100;-18.75709;9.70007;,
 -11.06100;-18.75709;0.58332;,
 -11.06100;17.66411;-3.71976;,
 -11.06100;15.63669;-7.77368;,
 -11.06100;-18.75709;-3.71976;,
 -11.06100;-18.75709;-7.77368;,
 -11.06100;13.03783;-12.32602;,
 -11.06100;5.22172;-16.52717;,
 -11.06100;-18.75709;-16.52717;,
 -11.06100;-18.75709;-12.32602;,
 -11.06100;5.22172;17.69379;,
 -11.06100;13.18681;13.64108;,
 -11.06100;-18.75709;13.64108;,
 -11.06100;-18.75709;17.69379;,
 -11.06100;-2.02942;-16.52717;,
 -11.06100;-18.75709;-16.52717;,
 -11.06100;-18.75709;17.69379;,
 -11.06100;-2.02942;17.69379;,
 10.64747;15.63669;9.70007;,
 10.64747;17.69393;5.18325;,
 10.64747;18.51711;0.58332;,
 10.64747;-18.75709;5.18325;,
 10.64747;-18.75709;9.70007;,
 10.64747;-18.75709;0.58332;,
 10.64747;17.66411;-3.71976;,
 10.64747;15.63669;-7.77368;,
 10.64747;-18.75709;-3.71976;,
 10.64747;-18.75709;-7.77368;,
 10.64747;13.03783;-12.32602;,
 10.64747;5.22172;-16.52717;,
 10.64747;-18.75709;-16.52717;,
 10.64747;-18.75709;-12.32602;,
 10.64747;5.22172;17.69379;,
 10.64747;13.18681;13.64108;,
 10.64747;-18.75709;13.64108;,
 10.64747;-18.75709;17.69379;,
 10.64747;-2.02942;-16.52717;,
 10.64747;-18.75709;-16.52717;,
 10.64747;-18.75709;17.69379;,
 10.64747;-2.02942;17.69379;,
 15.29933;15.63669;9.70007;,
 15.29933;17.69393;5.18325;,
 15.29933;18.51711;0.58332;,
 15.29933;-18.75709;5.18325;,
 15.29933;-18.75709;9.70007;,
 15.29933;-18.75709;0.58332;,
 15.29933;17.66411;-3.71976;,
 15.29933;15.63669;-7.77368;,
 15.29933;-18.75709;-3.71976;,
 15.29933;-18.75709;-7.77368;,
 15.29933;13.03783;-12.32602;,
 15.29933;5.22172;-16.52717;,
 15.29933;-18.75709;-16.52717;,
 15.29933;-18.75709;-12.32602;,
 15.29933;5.22172;17.69379;,
 15.29933;13.18681;13.64108;,
 15.29933;-18.75709;13.64108;,
 15.29933;-18.75709;17.69379;,
 15.29933;-2.02942;-16.52717;,
 15.29933;-18.75709;-16.52717;,
 15.29933;-18.75709;17.69379;,
 15.29933;-2.02942;17.69379;,
 24.99670;5.18090;5.18325;,
 24.99670;17.69393;5.18325;,
 24.99670;15.63669;9.70007;,
 24.99670;5.18090;9.70007;,
 24.99670;5.18090;0.58332;,
 24.99670;18.51711;0.58332;,
 -24.99670;5.18090;9.70007;,
 -24.99670;15.63669;9.70007;,
 -24.99670;17.69393;5.18325;,
 -24.99670;5.18090;5.18325;,
 -24.99670;18.51711;0.58332;,
 -24.99670;5.18090;0.58332;,
 24.99670;5.18090;-3.71976;,
 24.99670;17.66411;-3.71976;,
 24.99670;5.18090;-7.77359;,
 24.99670;15.63669;-7.77368;,
 -24.99670;17.66411;-3.71976;,
 -24.99670;5.18090;-3.71976;,
 -24.99670;15.63669;-7.77368;,
 -24.99670;5.18090;-7.77359;,
 24.99670;5.18090;-16.52717;,
 24.99670;5.22172;-16.52717;,
 24.99670;13.03783;-12.32602;,
 24.99670;5.18090;-12.32602;,
 -24.99670;5.18090;-12.32602;,
 -24.99670;13.03783;-12.32602;,
 -24.99670;5.22172;-16.52717;,
 -24.99670;5.18090;-16.52717;,
 24.99670;5.18090;13.64108;,
 24.99670;13.18681;13.64108;,
 24.99670;5.18090;17.69379;,
 -24.99670;5.18090;17.69379;,
 -24.99670;13.18681;13.64108;,
 -24.99670;5.18090;13.64108;,
 20.59202;5.18090;-16.52717;,
 20.59202;5.22172;-16.52717;,
 24.99670;5.22172;-16.52717;,
 24.99670;5.18090;-16.52717;,
 24.99670;5.18090;17.69379;,
 24.99670;5.22172;17.69379;,
 20.59202;5.22172;17.69379;,
 20.59202;5.18090;17.69379;,
 -24.99670;5.18090;-16.52717;,
 -24.99670;5.22172;-16.52717;,
 -20.69543;5.22172;-16.52717;,
 -20.69543;5.18090;-16.52717;,
 -20.69543;5.18090;17.69379;,
 -20.69543;5.22172;17.69379;,
 -24.99670;5.22172;17.69379;,
 -24.99670;5.18090;17.69379;,
 -15.71286;5.18090;-16.52717;,
 -15.71286;5.22172;-16.52717;,
 -15.71286;5.18090;17.69379;,
 -15.71286;5.22172;17.69379;,
 -11.06100;5.18090;-16.52717;,
 -11.06100;5.22172;-16.52717;,
 -11.06100;5.18090;17.69379;,
 -11.06100;5.22172;17.69379;,
 10.64747;5.18090;-16.52717;,
 10.64747;5.22172;-16.52717;,
 10.64747;5.18090;17.69379;,
 10.64747;5.22172;17.69379;,
 15.29933;5.18090;-16.52717;,
 15.29933;5.22172;-16.52717;,
 15.29933;5.22172;17.69379;,
 15.29933;5.18090;17.69379;,
 6.73295;5.15250;-17.20489;,
 6.73295;5.15250;-16.28469;,
 6.73295;-4.99482;-16.28469;,
 6.73295;-4.99482;-17.20489;,
 -6.73295;5.15250;-16.28469;,
 -6.73295;5.15250;-17.20489;,
 -6.73295;-4.99482;-17.20489;,
 -6.73295;-4.99482;-16.28469;,
 0.00000;-7.08216;-17.20489;,
 0.00000;5.15250;-17.20489;,
 6.73295;5.15250;-17.20489;,
 6.73295;-4.99482;-17.20489;,
 6.73295;-4.99482;-16.28469;,
 6.73295;5.15250;-16.28469;,
 0.00000;5.15250;-16.28469;,
 0.00000;-7.08216;-16.28469;,
 0.00000;5.15250;-17.20489;,
 6.73295;5.15250;-17.20489;,
 0.00000;-7.08216;-17.20489;,
 6.73295;-4.99482;-17.20489;,
 -6.73295;-4.99482;-17.20489;,
 -6.73295;5.15250;-17.20489;,
 -6.73295;5.15250;-16.28469;,
 -6.73295;-4.99482;-16.28469;,
 -6.73295;5.15250;-17.20489;,
 -6.73295;-4.99482;-17.20489;;
 
 212;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;5,4,12,13;,
 4;13,12,14,15;,
 4;10,16,17,11;,
 4;16,18,19,17;,
 4;20,21,22,23;,
 4;21,15,14,22;,
 4;24,25,26,27;,
 4;27,26,19,18;,
 4;28,29,30,31;,
 4;31,30,1,0;,
 4;32,33,34,35;,
 4;33,6,9,34;,
 4;36,37,38,39;,
 4;40,41,37,36;,
 4;42,43,44,45;,
 4;45,44,46,47;,
 4;48,49,41,40;,
 4;50,51,49,48;,
 4;47,46,52,53;,
 4;53,52,54,55;,
 4;56,57,58,59;,
 4;59,58,51,50;,
 4;60,61,62,63;,
 4;55,54,61,60;,
 4;64,65,66,67;,
 4;39,38,65,64;,
 4;68,69,70,71;,
 4;71,70,43,42;,
 4;72,73,74,75;,
 4;75,74,76,77;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;77,76,84,85;,
 4;85,84,86,87;,
 4;82,88,89,83;,
 4;88,90,91,89;,
 4;92,93,94,95;,
 4;93,87,86,94;,
 4;96,97,98,99;,
 4;99,98,91,90;,
 4;100,35,101,102;,
 4;102,101,73,72;,
 4;103,104,105,69;,
 4;104,78,81,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,36,39;,
 4;123,124,40,36;,
 4;125,126,42,45;,
 4;127,125,45,47;,
 4;124,128,48,40;,
 4;128,129,50,48;,
 4;130,127,47,53;,
 4;131,130,53,55;,
 4;132,133,56,59;,
 4;129,132,59,50;,
 4;134,135,60,63;,
 4;135,131,55,60;,
 4;136,137,64,67;,
 4;137,122,39,64;,
 4;138,139,68,71;,
 4;126,138,71,42;,
 4;140,141,116,115;,
 4;142,143,121,120;,
 4;144,145,123,122;,
 4;145,146,124,123;,
 4;147,148,126,125;,
 4;149,147,125,127;,
 4;146,150,128,124;,
 4;150,151,129,128;,
 4;152,149,127,130;,
 4;153,152,130,131;,
 4;154,155,133,132;,
 4;151,154,132,129;,
 4;156,157,135,134;,
 4;157,153,131,135;,
 4;158,159,137,136;,
 4;159,144,122,137;,
 4;160,161,139,138;,
 4;148,160,138,126;,
 4;162,163,141,140;,
 4;164,165,143,142;,
 4;166,167,145,144;,
 4;167,168,146,145;,
 4;169,170,148,147;,
 4;171,169,147,149;,
 4;168,172,150,146;,
 4;172,173,151,150;,
 4;174,171,149,152;,
 4;175,174,152,153;,
 4;176,177,155,154;,
 4;173,176,154,151;,
 4;178,179,157,156;,
 4;179,175,153,157;,
 4;180,181,159,158;,
 4;181,166,144,159;,
 4;182,183,161,160;,
 4;170,182,160,148;,
 4;184,185,163,162;,
 4;186,187,165,164;,
 4;188,0,3,189;,
 4;188,189,167,166;,
 4;189,3,5,190;,
 4;189,190,168,167;,
 4;191,7,6,192;,
 4;191,192,170,169;,
 4;193,10,7,191;,
 4;193,191,169,171;,
 4;190,5,13,194;,
 4;190,194,172,168;,
 4;194,13,15,195;,
 4;194,195,173,172;,
 4;196,16,10,193;,
 4;196,193,171,174;,
 4;197,18,16,196;,
 4;197,196,174,175;,
 4;198,21,20,199;,
 4;198,199,177,176;,
 4;195,15,21,198;,
 4;195,198,176,173;,
 4;200,24,27,201;,
 4;200,201,179,178;,
 4;201,27,18,197;,
 4;201,197,175,179;,
 4;202,28,31,203;,
 4;202,203,181,180;,
 4;203,31,0,188;,
 4;203,188,166,181;,
 4;204,33,32,205;,
 4;204,205,183,182;,
 4;192,6,33,204;,
 4;192,204,182,170;,
 4;206,109,108,207;,
 4;206,207,185,184;,
 4;208,111,110,209;,
 4;208,209,187,186;,
 4;210,211,212,213;,
 4;210,213,72,75;,
 4;214,215,211,210;,
 4;214,210,75,77;,
 4;216,217,218,219;,
 4;216,219,79,78;,
 4;219,218,220,221;,
 4;219,221,82,79;,
 4;222,223,215,214;,
 4;222,214,77,85;,
 4;224,225,223,222;,
 4;224,222,85,87;,
 4;221,220,226,227;,
 4;221,227,88,82;,
 4;227,226,228,229;,
 4;227,229,90,88;,
 4;230,231,232,233;,
 4;230,233,93,92;,
 4;233,232,225,224;,
 4;233,224,87,93;,
 4;234,235,236,237;,
 4;234,237,96,99;,
 4;229,228,235,234;,
 4;229,234,99,90;,
 4;238,239,29,240;,
 4;238,240,100,102;,
 4;213,212,239,238;,
 4;213,238,102,72;,
 4;241,66,242,243;,
 4;241,243,104,103;,
 4;243,242,217,216;,
 4;243,216,78,104;,
 4;244,245,246,247;,
 4;244,247,106,109;,
 4;248,249,250,251;,
 4;248,251,110,113;,
 4;252,253,254,255;,
 4;252,255,115,114;,
 4;256,257,258,259;,
 4;256,259,118,121;,
 4;260,140,115,255;,
 4;260,255,254,261;,
 4;262,263,257,256;,
 4;262,256,121,143;,
 4;264,162,140,260;,
 4;264,260,261,265;,
 4;266,267,263,262;,
 4;266,262,143,165;,
 4;268,184,162,264;,
 4;268,264,265,269;,
 4;270,271,267,266;,
 4;270,266,165,187;,
 4;244,109,206,272;,
 4;244,272,273,245;,
 4;272,206,184,268;,
 4;272,268,269,273;,
 4;251,250,274,275;,
 4;251,275,209,110;,
 4;275,274,271,270;,
 4;275,270,187,209;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,290,277,293;,
 4;291,294,295,278;,
 4;296,297,285,284;,
 4;291,290,298,299;,
 4;300,280,290,292;,
 4;283,301,294,291;;
 
 MeshMaterialList {
  3;
  212;
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
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1;;
  Material {
   0.037600;0.288800;0.721600;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.674400;0.000000;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  36;
  0.000000;0.244106;-0.969749;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.233169;0.972436;,
  0.000000;0.233169;0.972436;,
  0.000000;0.881493;0.472197;,
  0.000000;0.881493;0.472197;,
  0.000000;0.999957;-0.009305;,
  0.000000;0.881750;-0.471718;,
  0.000000;0.954674;0.297653;,
  0.000000;0.954674;0.297653;,
  0.000000;0.946135;-0.323773;,
  0.000000;0.698019;-0.716079;,
  0.000000;0.676239;0.736683;,
  0.000000;0.676239;0.736683;,
  0.000000;0.999957;-0.009305;,
  0.000000;0.881493;0.472197;,
  0.000000;0.954674;0.297653;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.881493;0.472197;,
  0.000000;0.999957;-0.009305;,
  0.000000;0.244106;-0.969749;,
  0.000000;0.881493;0.472197;,
  0.000000;0.698019;-0.716079;,
  0.000000;0.244106;-0.969749;,
  0.000000;0.946135;-0.323773;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.296115;-0.955152;-0.000000;,
  -0.296115;-0.955152;0.000000;;
  212;
  4;5,5,9,9;,
  4;9,9,6,14;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;14,6,10,10;,
  4;10,10,7,7;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,11,11,0;,
  4;11,7,7,11;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,12,12;,
  4;12,12,5,5;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;16,8,4,15;,
  4;14,6,8,16;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;10,10,6,14;,
  4;7,7,10,10;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,11,11;,
  4;11,11,7,7;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;13,13,3,3;,
  4;15,4,13,13;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,16,16,15;,
  4;16,22,14,16;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;22,10,10,14;,
  4;10,7,7,10;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;11,0,0,11;,
  4;7,11,11,7;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,12,13,3;,
  4;12,21,15,13;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;24,16,16,21;,
  4;16,14,22,16;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;14,10,10,22;,
  4;10,7,7,10;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;11,23,0,11;,
  4;7,11,11,7;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,12,12,3;,
  4;12,24,21,12;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;5,9,16,24;,
  4;9,6,14,16;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;6,10,10,14;,
  4;10,7,7,10;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;25,23,23,11;,
  4;7,25,11,7;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,12,12,3;,
  4;12,5,24,12;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;24,5,9,9;,
  4;24,9,9,5;,
  4;9,9,14,14;,
  4;9,14,6,9;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;14,14,10,27;,
  4;14,27,10,6;,
  4;27,10,7,7;,
  4;27,7,7,10;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;11,11,0,26;,
  4;11,26,23,25;,
  4;7,7,11,11;,
  4;7,11,25,7;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,12,12;,
  4;2,12,12,3;,
  4;12,12,5,24;,
  4;12,24,5,12;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;19,0,0,19;,
  4;19,19,19,19;,
  4;20,2,2,20;,
  4;20,20,20,20;,
  4;19,0,0,19;,
  4;19,19,19,19;,
  4;20,3,3,20;,
  4;20,20,20,20;,
  4;19,19,19,19;,
  4;19,19,0,0;,
  4;20,3,3,20;,
  4;20,20,20,20;,
  4;19,19,19,19;,
  4;19,19,0,23;,
  4;20,3,3,20;,
  4;20,20,20,20;,
  4;19,19,19,19;,
  4;19,19,23,23;,
  4;20,3,3,20;,
  4;20,20,20,20;,
  4;19,19,19,19;,
  4;19,19,26,0;,
  4;19,19,19,19;,
  4;19,19,23,26;,
  4;20,2,2,20;,
  4;20,20,20,20;,
  4;20,2,3,20;,
  4;20,20,20,20;,
  4;30,30,30,30;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,34,34;,
  4;29,29,29,29;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;35,35,33,33;;
 }
 MeshTextureCoords {
  302;
  0.870540;0.233590;,
  1.000000;0.233590;,
  1.000000;0.365580;,
  0.870540;0.365580;,
  1.000000;0.500000;,
  0.870540;0.500000;,
  0.870540;0.766410;,
  0.870540;0.634420;,
  1.000000;0.634420;,
  1.000000;0.766410;,
  0.870540;0.500000;,
  1.000000;0.500000;,
  1.000000;0.625750;,
  0.870540;0.625750;,
  1.000000;0.744210;,
  0.870540;0.744210;,
  0.870540;0.374250;,
  1.000000;0.374250;,
  0.870540;0.255790;,
  1.000000;0.255790;,
  0.870540;1.000000;,
  0.870540;0.877240;,
  1.000000;0.877240;,
  1.000000;1.000000;,
  0.870540;0.000000;,
  1.000000;0.000000;,
  1.000000;0.122760;,
  0.870540;0.122760;,
  0.870540;0.000000;,
  1.000000;0.000000;,
  1.000000;0.118430;,
  0.870540;0.118430;,
  0.870540;1.000000;,
  0.870540;0.881570;,
  1.000000;0.881570;,
  1.000000;1.000000;,
  0.112920;0.365580;,
  0.000000;0.365580;,
  0.000000;0.233590;,
  0.112920;0.233590;,
  0.112920;0.500000;,
  0.000000;0.500000;,
  0.112920;0.766410;,
  0.000000;0.766410;,
  0.000000;0.634420;,
  0.112920;0.634420;,
  0.000000;0.500000;,
  0.112920;0.500000;,
  0.112920;0.625750;,
  0.000000;0.625750;,
  0.112920;0.744210;,
  0.000000;0.744210;,
  0.000000;0.374250;,
  0.112920;0.374250;,
  0.000000;0.255790;,
  0.112920;0.255790;,
  0.112920;1.000000;,
  0.000000;1.000000;,
  0.000000;0.877240;,
  0.112920;0.877240;,
  0.112920;0.122760;,
  0.000000;0.122760;,
  0.000000;0.000000;,
  0.112920;0.000000;,
  0.112920;0.118430;,
  0.000000;0.118430;,
  0.000000;0.000000;,
  0.112920;0.000000;,
  0.112920;1.000000;,
  0.000000;1.000000;,
  0.000000;0.881570;,
  0.112920;0.881570;,
  0.766410;0.513640;,
  0.766410;1.000000;,
  0.634420;1.000000;,
  0.634420;0.541090;,
  0.500000;1.000000;,
  0.500000;0.551230;,
  0.233590;0.513640;,
  0.365580;0.541090;,
  0.365580;1.000000;,
  0.233590;1.000000;,
  0.500000;0.551230;,
  0.500000;1.000000;,
  0.374250;1.000000;,
  0.374250;0.540720;,
  0.255790;1.000000;,
  0.255790;0.513640;,
  0.625750;0.540720;,
  0.625750;1.000000;,
  0.744210;0.513640;,
  0.744210;1.000000;,
  0.000000;0.302400;,
  0.122760;0.473890;,
  0.122760;1.000000;,
  0.000000;1.000000;,
  1.000000;0.302400;,
  1.000000;1.000000;,
  0.877240;1.000000;,
  0.877240;0.473890;,
  1.000000;0.302400;,
  0.881570;1.000000;,
  0.881570;0.476340;,
  0.000000;0.302400;,
  0.118430;0.476340;,
  0.118430;1.000000;,
  1.000000;0.302400;,
  1.000000;1.000000;,
  0.870540;1.000000;,
  0.870540;0.302400;,
  0.129460;0.302400;,
  0.129460;1.000000;,
  0.000000;1.000000;,
  0.000000;0.302400;,
  0.000000;0.302400;,
  0.112920;0.302400;,
  0.112920;1.000000;,
  0.000000;1.000000;,
  1.000000;0.302400;,
  1.000000;1.000000;,
  0.887080;1.000000;,
  0.887080;0.302400;,
  0.177430;0.233590;,
  0.177430;0.365580;,
  0.177430;0.500000;,
  0.177430;0.634420;,
  0.177430;0.766410;,
  0.177430;0.500000;,
  0.177430;0.625750;,
  0.177430;0.744210;,
  0.177430;0.374250;,
  0.177430;0.255790;,
  0.177430;0.877240;,
  0.177430;1.000000;,
  0.177430;0.000000;,
  0.177430;0.122760;,
  0.177430;0.000000;,
  0.177430;0.118430;,
  0.177430;0.881570;,
  0.177430;1.000000;,
  0.177430;0.302400;,
  0.177430;1.000000;,
  0.822570;1.000000;,
  0.822570;0.302400;,
  0.247740;0.233590;,
  0.247740;0.365580;,
  0.247740;0.500000;,
  0.247740;0.634420;,
  0.247740;0.766410;,
  0.247740;0.500000;,
  0.247740;0.625750;,
  0.247740;0.744210;,
  0.247740;0.374250;,
  0.247740;0.255790;,
  0.247740;0.877240;,
  0.247740;1.000000;,
  0.247740;0.000000;,
  0.247740;0.122760;,
  0.247740;0.000000;,
  0.247740;0.118430;,
  0.247740;0.881570;,
  0.247740;1.000000;,
  0.247740;0.302400;,
  0.247740;1.000000;,
  0.752260;1.000000;,
  0.752260;0.302400;,
  0.712980;0.233590;,
  0.712980;0.365580;,
  0.712980;0.500000;,
  0.712980;0.634420;,
  0.712980;0.766410;,
  0.712980;0.500000;,
  0.712980;0.625750;,
  0.712980;0.744210;,
  0.712980;0.374250;,
  0.712980;0.255790;,
  0.712980;0.877240;,
  0.712980;1.000000;,
  0.712980;0.000000;,
  0.712980;0.122760;,
  0.712980;0.000000;,
  0.712980;0.118430;,
  0.712980;0.881570;,
  0.712980;1.000000;,
  0.712980;0.302400;,
  0.712980;1.000000;,
  0.287020;1.000000;,
  0.287020;0.302400;,
  0.793620;0.233590;,
  0.793620;0.365580;,
  0.793620;0.500000;,
  0.793620;0.634420;,
  0.793620;0.766410;,
  0.793620;0.500000;,
  0.793620;0.625750;,
  0.793620;0.744210;,
  0.793620;0.374250;,
  0.793620;0.255790;,
  0.793620;0.877240;,
  0.793620;1.000000;,
  0.793620;0.000000;,
  0.793620;0.122760;,
  0.793620;0.000000;,
  0.793620;0.118430;,
  0.793620;0.881570;,
  0.793620;1.000000;,
  0.793620;0.302400;,
  0.793620;1.000000;,
  0.206380;1.000000;,
  0.206380;0.302400;,
  0.634420;0.343280;,
  0.634420;0.000000;,
  0.766410;0.000000;,
  0.766410;0.304000;,
  0.500000;0.357790;,
  0.500000;0.000000;,
  0.233590;0.304000;,
  0.233590;0.000000;,
  0.365580;0.000000;,
  0.365580;0.343280;,
  0.500000;0.000000;,
  0.500000;0.357790;,
  0.374250;0.342750;,
  0.374250;0.000000;,
  0.255790;0.304000;,
  0.255790;0.000000;,
  0.625750;0.000000;,
  0.625750;0.342750;,
  0.744210;0.000000;,
  0.744210;0.304000;,
  0.000000;0.001700;,
  0.000000;0.000000;,
  0.122760;0.000000;,
  0.122760;0.247110;,
  0.877240;0.247110;,
  0.877240;0.000000;,
  1.000000;0.000000;,
  1.000000;0.001700;,
  0.881570;0.250630;,
  0.881570;0.000000;,
  1.000000;0.001700;,
  0.000000;0.001700;,
  0.118430;0.000000;,
  0.118430;0.250630;,
  0.870540;0.001700;,
  0.870540;0.000000;,
  1.000000;0.000000;,
  1.000000;0.001700;,
  0.000000;0.001700;,
  0.000000;0.000000;,
  0.129460;0.000000;,
  0.129460;0.001700;,
  0.000000;0.001700;,
  0.000000;0.000000;,
  0.112920;0.000000;,
  0.112920;0.001700;,
  0.887080;0.001700;,
  0.887080;0.000000;,
  1.000000;0.000000;,
  1.000000;0.001700;,
  0.177430;0.001700;,
  0.177430;0.000000;,
  0.822570;0.001700;,
  0.822570;0.000000;,
  0.247740;0.001700;,
  0.247740;0.000000;,
  0.752260;0.001700;,
  0.752260;0.000000;,
  0.712980;0.001700;,
  0.712980;0.000000;,
  0.287020;0.001700;,
  0.287020;0.000000;,
  0.793620;0.001700;,
  0.793620;0.000000;,
  0.206380;0.000000;,
  0.206380;0.001700;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;;
 }
}
