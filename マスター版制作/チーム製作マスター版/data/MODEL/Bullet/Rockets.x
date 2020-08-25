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
 287;
 0.20866;-12.78182;-1.09901;,
 0.77098;-12.78182;-0.69045;,
 -0.13887;-13.06203;-0.02940;,
 0.98576;-12.78182;-0.02940;,
 -0.48641;-12.78182;-1.09901;,
 0.77098;-12.78182;0.63164;,
 -1.04873;-12.78182;-0.69045;,
 0.20866;-12.78182;1.04019;,
 -1.26350;-12.78182;-0.02940;,
 -0.48641;-12.78182;1.04019;,
 -1.04873;-12.78182;0.63164;,
 1.22812;-12.17714;-1.02258;,
 0.38328;-12.17714;-1.63640;,
 1.55082;-12.17714;-0.02940;,
 -0.66101;-12.17714;-1.63640;,
 0.55619;-10.86708;-2.16859;,
 1.68082;-10.86708;-1.35150;,
 2.11041;-10.86708;-0.02940;,
 1.22812;-12.17714;0.96378;,
 -0.83393;-10.86708;-2.16859;,
 -1.50587;-12.17714;-1.02258;,
 1.68082;-10.86708;1.29271;,
 0.38328;-12.17714;1.57760;,
 -1.82857;-12.17714;-0.02940;,
 -1.95857;-10.86708;-1.35150;,
 -0.66101;-12.17714;1.57760;,
 -1.50587;-12.17714;0.96378;,
 0.55619;-10.86708;2.10979;,
 -2.38814;-10.86708;-0.02940;,
 -0.83393;-10.86708;2.10979;,
 -1.95857;-10.86708;1.29271;,
 5.09295;6.35607;-0.01521;,
 5.09295;6.38353;-0.15815;,
 5.50022;7.19822;-0.01521;,
 5.50022;7.19822;-0.15815;,
 -0.14659;6.28580;-5.15114;,
 -0.14659;7.12797;-5.56118;,
 -0.00504;6.31330;-5.15114;,
 -0.00504;7.12797;-5.56118;,
 5.09295;6.38353;0.12634;,
 5.50022;7.19822;0.12634;,
 -0.28954;6.31330;-5.15114;,
 -0.28954;7.12797;-5.56118;,
 5.50022;7.19822;-0.29568;,
 0.13114;7.12797;-5.56118;,
 5.50022;7.19822;0.26254;,
 -0.42706;7.12797;-5.56118;,
 2.11041;6.38353;-0.15815;,
 2.11041;7.19822;-0.15815;,
 2.11041;7.19822;-0.29568;,
 2.11041;7.19822;0.26254;,
 2.11041;7.19822;0.12634;,
 2.11041;6.38353;0.12634;,
 0.55619;-10.86708;-2.16859;,
 0.55619;7.39589;-2.16859;,
 1.68082;-10.86708;-1.35150;,
 1.68082;7.39589;-1.35150;,
 2.11041;7.39589;-0.02940;,
 2.11041;-10.86708;-0.02940;,
 -2.38814;7.18984;-0.29568;,
 -2.38814;7.18984;-0.15950;,
 -2.38814;6.37033;-0.15950;,
 -2.38814;6.37033;0.12500;,
 -2.38814;7.18984;0.12500;,
 -2.38814;7.18984;0.26254;,
 1.68082;7.39589;1.29271;,
 1.68082;-10.86708;1.29271;,
 -0.14933;6.28580;5.09237;,
 -0.00639;6.31330;5.09237;,
 -0.14933;7.12797;5.50242;,
 -0.00639;7.12797;5.50242;,
 -0.29088;6.31330;5.09237;,
 -0.29088;7.12797;5.50242;,
 -5.37070;6.34272;-0.01795;,
 -5.77797;7.18984;-0.01795;,
 -5.37070;6.37033;-0.15950;,
 -5.77797;7.18984;-0.15950;,
 -5.37070;6.37033;0.12500;,
 -5.77797;7.18984;0.12500;,
 0.13114;7.12797;5.50242;,
 -1.95857;-10.86708;-1.35150;,
 -1.95857;7.39589;-1.35150;,
 -0.83393;-10.86708;-2.16859;,
 -0.83394;7.39589;-2.16859;,
 -5.77797;7.18984;-0.29568;,
 -0.42706;7.12797;5.50242;,
 -5.77797;7.18984;0.26254;,
 1.68082;12.95393;-1.35150;,
 0.55619;12.95393;-2.16859;,
 -0.13887;12.95393;-0.02940;,
 2.11041;12.95393;-0.02940;,
 -0.83394;12.95393;-2.16859;,
 0.55619;-10.86708;2.10979;,
 0.55619;7.39589;2.10980;,
 1.68082;12.95393;1.29271;,
 -1.95858;12.95393;-1.35150;,
 0.55619;12.95393;2.10980;,
 -2.38814;12.95393;-0.02940;,
 -0.83394;12.95393;2.10980;,
 -1.95858;12.95393;1.29271;,
 -0.83393;-10.86708;2.10979;,
 -0.83394;7.39589;2.10980;,
 -1.95857;-10.86708;1.29271;,
 -1.95857;7.39589;1.29271;,
 5.63317;7.57752;-0.29568;,
 5.63317;7.57752;-0.15815;,
 0.13114;7.50727;-5.69134;,
 -0.00504;7.50727;-5.69134;,
 5.63317;7.57752;-0.01521;,
 -0.14659;7.50727;-5.69134;,
 5.63317;7.57752;0.12634;,
 -0.28954;7.50727;-5.69134;,
 5.63317;7.57752;0.26254;,
 -0.42706;7.50727;-5.69134;,
 5.73188;8.36035;-0.15815;,
 5.73188;8.36035;-0.29568;,
 0.13114;8.29008;-5.79005;,
 -0.00504;8.29008;-5.79005;,
 2.11041;6.35607;-0.01521;,
 -0.14659;6.28580;-2.16859;,
 -0.00504;6.31330;-2.16859;,
 5.73188;8.36035;-0.01521;,
 -0.14659;8.29008;-5.79005;,
 -0.28954;6.31330;-2.16859;,
 5.73188;8.36035;0.12634;,
 -0.28954;8.29008;-5.79005;,
 0.13114;7.12797;-2.16859;,
 5.73188;8.36035;0.26254;,
 -0.42706;8.29008;-5.79005;,
 -0.42706;7.12797;-2.16859;,
 5.63317;7.57752;-0.29568;,
 5.50022;7.19822;-0.29568;,
 2.11041;7.57752;-0.29568;,
 5.50022;7.19822;0.26254;,
 2.11041;7.57752;0.26254;,
 5.63317;7.57752;0.26254;,
 5.73188;8.36035;-0.29568;,
 2.11041;8.36035;-0.29568;,
 0.13114;7.50727;-2.16859;,
 0.13114;7.50727;-5.69134;,
 0.13114;8.29008;-2.16859;,
 0.13114;8.29008;-5.79005;,
 2.11041;7.19822;-0.01521;,
 2.11041;8.36035;0.26254;,
 5.73188;8.36035;0.26254;,
 -0.42706;8.29008;-5.79005;,
 -0.42706;7.50727;-5.69134;,
 -0.42706;8.29008;-2.16859;,
 -0.42706;7.50727;-2.16859;,
 2.11041;8.36035;-0.29568;,
 2.11041;8.36035;-0.15815;,
 0.13114;8.29008;-2.16859;,
 -0.00504;8.29008;-2.16859;,
 2.11041;8.36035;-0.01521;,
 -0.14659;8.29008;-2.16859;,
 2.11041;8.36035;0.12634;,
 -0.28954;8.29008;-2.16859;,
 2.11041;8.36035;0.26254;,
 -0.42706;8.29008;-2.16859;,
 2.11041;7.57752;-0.15815;,
 2.11041;7.57752;-0.01521;,
 2.11041;7.57752;0.12634;,
 2.11041;8.36035;-0.15815;,
 2.11041;8.36035;-0.01521;,
 2.11041;8.36035;0.12634;,
 1.68082;12.95393;-1.35150;,
 0.55619;12.95393;-2.16859;,
 2.11041;12.95393;-0.02940;,
 -2.38814;6.34494;-0.02940;,
 -2.38814;7.18984;-0.02940;,
 -2.38814;7.18984;-0.01795;,
 -2.38814;6.34272;-0.01795;,
 -2.38814;7.57134;-0.29568;,
 -2.38814;7.57134;-0.15950;,
 -0.00639;6.31330;2.10980;,
 -0.14933;6.28580;2.10980;,
 -0.29088;6.31330;2.10980;,
 -2.38814;7.57134;0.12500;,
 -2.38814;7.57134;-0.01795;,
 1.68082;12.95393;1.29271;,
 -2.38814;7.57134;0.26254;,
 0.13114;7.12797;2.10980;,
 -2.38814;8.35882;-0.15950;,
 -2.38814;8.35882;-0.29568;,
 -2.38814;7.57134;-0.02940;,
 -2.38814;8.35882;-0.02940;,
 -2.38814;8.35882;-0.01795;,
 -0.42706;7.12797;2.10980;,
 -2.38814;8.35882;0.12500;,
 -2.38814;8.35882;0.26254;,
 -0.83394;12.95393;-2.16859;,
 -1.95858;12.95393;-1.35150;,
 -5.77797;7.18984;-0.29568;,
 -5.91091;7.57134;-0.29568;,
 -5.91091;7.57134;0.26254;,
 -5.77797;7.18984;0.26254;,
 0.55619;12.95393;2.10980;,
 0.13114;8.29008;5.73127;,
 0.13114;7.50727;5.63257;,
 0.13114;8.29008;2.10980;,
 0.13114;7.50727;2.10980;,
 -6.00961;8.35882;-0.29568;,
 -0.42706;7.50727;2.10980;,
 -0.42706;7.50727;5.63257;,
 -0.42706;8.29008;2.10980;,
 -0.42706;8.29008;5.73127;,
 -0.00639;8.29008;2.10980;,
 -0.00639;8.29008;5.73127;,
 0.13114;8.29008;2.10980;,
 0.13114;8.29008;5.73127;,
 -6.00961;8.35882;0.26254;,
 -0.14933;8.29008;2.10980;,
 -0.14933;8.29008;5.73127;,
 -6.00961;8.35882;-0.29568;,
 -6.00961;8.35882;-0.15950;,
 -2.38814;8.35882;-0.29568;,
 -2.38814;8.35882;-0.15950;,
 -0.29088;8.29008;2.10980;,
 -0.29088;8.29008;5.73127;,
 0.13114;7.50727;5.63257;,
 -0.00639;7.50727;5.63257;,
 -0.42706;8.29008;2.10980;,
 -0.42706;8.29008;5.73127;,
 -0.14933;7.50727;5.63257;,
 -2.38814;8.35882;-0.01795;,
 -6.00961;8.35882;-0.01795;,
 -2.38814;8.35882;0.12500;,
 -6.00961;8.35882;0.12500;,
 -5.91091;7.57134;-0.29568;,
 -5.91091;7.57134;-0.15950;,
 -0.29088;7.50727;5.63257;,
 -6.00961;8.35882;0.26254;,
 -2.38814;8.35882;0.26254;,
 -5.91091;7.57134;-0.01795;,
 -0.42706;7.50727;5.63257;,
 -5.91091;7.57134;0.12500;,
 -5.91091;7.57134;0.26254;,
 -1.95858;12.95393;1.29271;,
 -0.83394;12.95393;2.10980;,
 0.13114;7.12797;-5.56118;,
 0.13114;7.39589;-2.16859;,
 -0.42706;7.12797;-5.56118;,
 -0.42706;7.39589;-2.16859;,
 -2.38814;7.39589;-0.02940;,
 0.13114;7.12797;5.50242;,
 0.13114;7.39589;2.10980;,
 -0.42706;7.12797;5.50242;,
 -0.42706;7.39589;2.10980;,
 -2.38814;8.35882;-0.02940;,
 -2.38814;7.39589;-0.02940;,
 -1.95857;7.39589;-1.35150;,
 -2.38814;7.18984;-0.02940;,
 -1.95857;-10.86708;-1.35150;,
 -2.38814;6.34494;-0.02940;,
 -2.38814;-10.86708;-0.02940;,
 -1.95858;12.95393;-1.35150;,
 -2.38814;12.95393;-0.02940;,
 -2.38814;7.57134;-0.02940;,
 -2.38814;8.35882;-0.02940;,
 -0.42706;7.39589;-2.16859;,
 -0.42706;7.12797;-2.16859;,
 -0.28954;6.31330;-2.16859;,
 -0.14659;6.28580;-2.16859;,
 0.13114;7.39589;-2.16859;,
 0.13114;7.12797;-2.16859;,
 -0.00504;6.31330;-2.16859;,
 0.13114;7.39589;2.10980;,
 0.13114;7.12797;2.10980;,
 -0.00639;6.31330;2.10980;,
 -0.14933;6.28580;2.10980;,
 -0.42706;7.39589;2.10980;,
 -0.42706;7.12797;2.10980;,
 -0.29088;6.31330;2.10980;,
 0.13114;7.50727;-2.16859;,
 -0.42706;7.50727;-2.16859;,
 -0.42706;8.29008;-2.16859;,
 -0.28954;8.29008;-2.16859;,
 -0.14659;8.29008;-2.16859;,
 -0.00504;8.29008;-2.16859;,
 0.13114;8.29008;-2.16859;,
 -0.42706;7.50727;2.10980;,
 0.13114;7.50727;2.10980;,
 0.13114;8.29008;2.10980;,
 -0.00639;8.29008;2.10980;,
 -0.14933;8.29008;2.10980;,
 -0.29088;8.29008;2.10980;,
 -0.42706;8.29008;2.10980;;
 
 382;
 3;0,1,2;,
 3;1,3,2;,
 3;4,0,2;,
 3;3,5,2;,
 3;6,4,2;,
 3;5,7,2;,
 3;8,6,2;,
 3;7,9,2;,
 3;10,8,2;,
 3;9,10,2;,
 3;1,0,11;,
 3;11,0,12;,
 3;11,13,1;,
 3;1,13,3;,
 3;14,12,4;,
 3;4,12,0;,
 3;12,15,11;,
 3;11,15,16;,
 3;16,17,11;,
 3;11,17,13;,
 3;13,18,3;,
 3;3,18,5;,
 3;19,15,14;,
 3;14,15,12;,
 3;4,6,14;,
 3;14,6,20;,
 3;17,21,13;,
 3;13,21,18;,
 3;7,5,22;,
 3;22,5,18;,
 3;23,20,8;,
 3;8,20,6;,
 3;20,24,14;,
 3;14,24,19;,
 3;22,25,7;,
 3;7,25,9;,
 3;26,23,10;,
 3;10,23,8;,
 3;18,21,22;,
 3;22,21,27;,
 3;10,9,26;,
 3;26,9,25;,
 3;28,24,23;,
 3;23,24,20;,
 3;27,29,22;,
 3;22,29,25;,
 3;30,28,26;,
 3;26,28,23;,
 3;25,29,26;,
 3;26,29,30;,
 3;31,32,33;,
 3;33,32,34;,
 3;35,36,37;,
 3;37,36,38;,
 3;31,33,39;,
 3;39,33,40;,
 3;35,41,36;,
 3;36,41,42;,
 3;43,34,32;,
 3;44,37,38;,
 3;45,39,40;,
 3;46,42,41;,
 3;47,48,49;,
 3;50,51,52;,
 3;53,54,55;,
 3;55,54,56;,
 3;56,57,55;,
 3;55,57,58;,
 3;59,60,61;,
 3;62,63,64;,
 3;57,65,58;,
 3;58,65,66;,
 3;67,68,69;,
 3;69,68,70;,
 3;67,69,71;,
 3;71,69,72;,
 3;73,74,75;,
 3;75,74,76;,
 3;73,77,74;,
 3;74,77,78;,
 3;79,70,68;,
 3;80,81,82;,
 3;82,81,83;,
 3;84,75,76;,
 3;85,71,72;,
 3;86,78,77;,
 3;87,88,89;,
 3;90,87,89;,
 3;88,91,89;,
 3;66,65,92;,
 3;92,65,93;,
 3;94,90,89;,
 3;91,95,89;,
 3;96,94,89;,
 3;95,97,89;,
 3;98,96,89;,
 3;97,99,89;,
 3;99,98,89;,
 3;100,101,102;,
 3;102,101,103;,
 3;104,105,43;,
 3;43,105,34;,
 3;44,38,106;,
 3;106,38,107;,
 3;33,34,108;,
 3;108,34,105;,
 3;107,38,109;,
 3;109,38,36;,
 3;110,40,108;,
 3;108,40,33;,
 3;36,42,109;,
 3;109,42,111;,
 3;45,40,112;,
 3;112,40,110;,
 3;113,111,46;,
 3;46,111,42;,
 3;114,105,115;,
 3;115,105,104;,
 3;106,107,116;,
 3;116,107,117;,
 3;31,118,32;,
 3;32,118,47;,
 3;35,37,119;,
 3;119,37,120;,
 3;108,105,121;,
 3;121,105,114;,
 3;117,107,122;,
 3;122,107,109;,
 3;31,39,118;,
 3;118,39,52;,
 3;41,35,123;,
 3;123,35,119;,
 3;124,110,121;,
 3;121,110,108;,
 3;109,111,122;,
 3;122,111,125;,
 3;43,32,49;,
 3;49,32,47;,
 3;44,126,37;,
 3;37,126,120;,
 3;112,110,127;,
 3;127,110,124;,
 3;125,111,128;,
 3;128,111,113;,
 3;52,39,50;,
 3;50,39,45;,
 3;46,41,129;,
 3;129,41,123;,
 3;130,131,132;,
 3;132,131,49;,
 3;50,133,134;,
 3;134,133,135;,
 3;136,130,137;,
 3;137,130,132;,
 3;138,139,140;,
 3;140,139,141;,
 3;118,142,47;,
 3;47,142,48;,
 3;51,142,52;,
 3;52,142,118;,
 3;134,135,143;,
 3;143,135,144;,
 3;145,146,147;,
 3;147,146,148;,
 3;115,149,114;,
 3;114,149,150;,
 3;116,117,151;,
 3;151,117,152;,
 3;153,121,150;,
 3;150,121,114;,
 3;152,117,154;,
 3;154,117,122;,
 3;153,155,121;,
 3;121,155,124;,
 3;154,122,156;,
 3;156,122,125;,
 3;127,124,157;,
 3;157,124,155;,
 3;156,125,158;,
 3;158,125,128;,
 3;49,48,132;,
 3;132,48,159;,
 3;48,142,159;,
 3;159,142,160;,
 3;142,51,160;,
 3;160,51,161;,
 3;134,161,50;,
 3;50,161,51;,
 3;132,159,137;,
 3;137,159,162;,
 3;159,160,162;,
 3;162,160,163;,
 3;160,161,163;,
 3;163,161,164;,
 3;161,134,164;,
 3;164,134,143;,
 3;56,54,165;,
 3;165,54,166;,
 3;167,57,165;,
 3;165,57,56;,
 3;168,61,169;,
 3;169,61,60;,
 3;169,170,168;,
 3;168,170,171;,
 3;171,170,62;,
 3;62,170,63;,
 3;172,173,59;,
 3;59,173,60;,
 3;174,68,175;,
 3;175,68,67;,
 3;175,67,176;,
 3;176,67,71;,
 3;63,170,177;,
 3;177,170,178;,
 3;73,171,77;,
 3;77,171,62;,
 3;179,65,167;,
 3;167,65,57;,
 3;64,63,180;,
 3;180,63,177;,
 3;79,68,181;,
 3;181,68,174;,
 3;61,75,59;,
 3;59,75,84;,
 3;173,172,182;,
 3;182,172,183;,
 3;184,173,185;,
 3;185,173,182;,
 3;185,186,184;,
 3;184,186,178;,
 3;176,71,187;,
 3;187,71,85;,
 3;177,178,188;,
 3;188,178,186;,
 3;86,77,64;,
 3;64,77,62;,
 3;180,177,189;,
 3;189,177,188;,
 3;83,81,190;,
 3;190,81,191;,
 3;59,192,172;,
 3;172,192,193;,
 3;194,195,180;,
 3;180,195,64;,
 3;93,65,196;,
 3;196,65,179;,
 3;197,198,199;,
 3;199,198,200;,
 3;172,193,183;,
 3;183,193,201;,
 3;202,203,204;,
 3;204,203,205;,
 3;206,207,208;,
 3;208,207,209;,
 3;210,194,189;,
 3;189,194,180;,
 3;211,212,206;,
 3;206,212,207;,
 3;213,214,215;,
 3;215,214,216;,
 3;217,218,211;,
 3;211,218,212;,
 3;219,220,79;,
 3;79,220,70;,
 3;221,222,217;,
 3;217,222,218;,
 3;69,70,223;,
 3;223,70,220;,
 3;224,225,226;,
 3;226,225,227;,
 3;84,76,228;,
 3;228,76,229;,
 3;230,72,223;,
 3;223,72,69;,
 3;231,232,227;,
 3;227,232,226;,
 3;229,76,233;,
 3;233,76,74;,
 3;85,72,234;,
 3;234,72,230;,
 3;74,78,233;,
 3;233,78,235;,
 3;236,235,86;,
 3;86,235,78;,
 3;207,220,209;,
 3;209,220,219;,
 3;223,220,212;,
 3;212,220,207;,
 3;228,229,213;,
 3;213,229,214;,
 3;218,230,212;,
 3;212,230,223;,
 3;214,229,225;,
 3;225,229,233;,
 3;234,230,222;,
 3;222,230,218;,
 3;233,235,225;,
 3;225,235,227;,
 3;103,101,237;,
 3;237,101,238;,
 3;227,235,231;,
 3;231,235,236;,
 3;139,138,239;,
 3;138,240,239;,
 3;126,239,240;,
 3;146,241,148;,
 3;148,241,242;,
 3;241,129,242;,
 3;171,73,168;,
 3;73,75,168;,
 3;75,61,168;,
 3;169,60,243;,
 3;60,173,243;,
 3;173,184,243;,
 3;170,169,178;,
 3;169,243,178;,
 3;243,184,178;,
 3;198,244,200;,
 3;200,244,245;,
 3;244,181,245;,
 3;203,202,246;,
 3;202,247,246;,
 3;187,246,247;,
 3;224,248,225;,
 3;216,214,248;,
 3;248,214,225;,
 3;249,250,251;,
 3;250,252,251;,
 3;251,252,253;,
 3;252,254,253;,
 3;103,249,102;,
 3;249,251,102;,
 3;251,253,102;,
 3;253,254,102;,
 3;255,250,256;,
 3;249,257,250;,
 3;257,258,250;,
 3;250,258,256;,
 3;256,258,237;,
 3;249,103,257;,
 3;257,103,258;,
 3;258,103,237;,
 3;83,259,82;,
 3;259,260,82;,
 3;260,261,82;,
 3;261,262,82;,
 3;263,54,264;,
 3;54,53,264;,
 3;264,53,265;,
 3;265,53,262;,
 3;262,53,82;,
 3;93,266,92;,
 3;266,267,92;,
 3;267,268,92;,
 3;268,269,92;,
 3;270,101,271;,
 3;101,100,271;,
 3;271,100,272;,
 3;272,100,269;,
 3;269,100,92;,
 3;166,54,190;,
 3;263,273,54;,
 3;259,83,274;,
 3;83,190,274;,
 3;274,190,275;,
 3;275,190,276;,
 3;276,190,277;,
 3;277,190,278;,
 3;278,190,279;,
 3;273,279,54;,
 3;54,279,190;,
 3;238,101,196;,
 3;270,280,101;,
 3;266,93,281;,
 3;93,196,281;,
 3;281,196,282;,
 3;282,196,283;,
 3;283,196,284;,
 3;284,196,285;,
 3;285,196,286;,
 3;280,286,101;,
 3;101,286,196;;
 
 MeshMaterialList {
  4;
  382;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.357600;0.404800;0.235200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.081600;0.081600;0.081600;1.000000;;
   5.000000;
   0.300000;0.300000;0.300000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.480000;0.480000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  180;
  0.217542;-0.831418;-0.511292;,
  0.476525;-0.831420;-0.285772;,
  0.000000;-1.000000;0.000001;,
  0.553491;-0.831419;0.048895;,
  -0.124538;-0.831416;-0.541514;,
  0.419045;-0.831420;0.364886;,
  -0.419049;-0.831417;-0.364889;,
  0.124536;-0.831420;0.541509;,
  -0.553491;-0.831419;-0.048895;,
  -0.217540;-0.831419;0.511292;,
  -0.476523;-0.831420;0.285772;,
  0.206231;-0.575483;-0.791383;,
  0.667267;-0.525635;-0.527695;,
  0.836993;-0.547128;0.009696;,
  -0.295671;-0.525634;-0.797676;,
  0.198066;-0.177815;-0.963925;,
  0.801718;-0.134005;-0.582487;,
  0.979538;-0.201216;0.004049;,
  0.688921;-0.575490;0.440681;,
  -0.202275;-0.088516;-0.975320;,
  -0.688920;-0.575487;-0.440686;,
  0.779572;-0.267326;0.566397;,
  0.295670;-0.525637;0.797674;,
  -0.836994;-0.547125;-0.009696;,
  -0.838171;-0.200534;-0.507204;,
  -0.206229;-0.575486;0.791382;,
  -0.667265;-0.525637;0.527696;,
  0.202276;-0.088515;0.975320;,
  -0.968700;-0.240620;0.061011;,
  -0.198063;-0.177815;0.963926;,
  -0.850457;-0.099941;0.516463;,
  0.896058;-0.443066;-0.027802;,
  0.914292;-0.405055;0.000137;,
  0.900253;-0.435368;0.000410;,
  0.000138;-0.404692;-0.914453;,
  0.028268;-0.445487;-0.894842;,
  0.000413;-0.437761;-0.899091;,
  0.896051;-0.443063;0.028075;,
  -0.027993;-0.445490;-0.894849;,
  0.928936;-0.370240;-0.000000;,
  0.925779;-0.378064;-0.000000;,
  0.000000;-0.387977;-0.921669;,
  0.000000;-0.367000;-0.930221;,
  0.928936;-0.370240;-0.000000;,
  0.000000;-0.375413;-0.926858;,
  0.920920;-0.389752;-0.000000;,
  0.000000;-0.367000;-0.930221;,
  -1.000000;0.000000;0.000000;,
  0.246693;0.000000;-0.969094;,
  0.809015;0.000000;-0.587788;,
  0.994186;0.000000;-0.107680;,
  1.000000;0.000000;0.000000;,
  0.809014;0.000000;0.587790;,
  0.027994;-0.445494;0.894847;,
  -0.000137;-0.404690;0.914454;,
  -0.000412;-0.437765;0.899089;,
  -0.028268;-0.445491;0.894840;,
  -0.915169;-0.403070;-0.000137;,
  -0.897084;-0.440967;-0.028098;,
  -0.901253;-0.433292;-0.000411;,
  -0.897091;-0.440970;0.027824;,
  0.000000;-0.366992;0.930224;,
  0.000000;-0.375406;0.926861;,
  -0.845433;-0.000000;-0.534082;,
  -0.246693;-0.000000;-0.969094;,
  -0.921737;-0.387815;0.000000;,
  -0.929681;-0.368365;0.000000;,
  0.000000;-0.387972;0.921671;,
  -0.926553;-0.376164;0.000000;,
  0.000000;1.000000;0.000000;,
  0.246691;-0.000000;0.969094;,
  -0.246690;-0.000000;0.969095;,
  -0.867607;-0.000000;0.497251;,
  0.973371;-0.229235;-0.000000;,
  0.976738;-0.214435;-0.000000;,
  0.000000;-0.192497;-0.981298;,
  0.000000;-0.259299;-0.965797;,
  0.964647;-0.263546;-0.000000;,
  0.980875;-0.194637;-0.000000;,
  0.000000;-0.211685;-0.977338;,
  0.964647;-0.263546;-0.000000;,
  0.000000;-0.226031;-0.974120;,
  0.992144;-0.125103;-0.000000;,
  0.000000;-0.125108;-0.992143;,
  0.000000;-1.000000;0.000914;,
  0.190696;-0.981649;-0.000000;,
  0.065218;-0.997871;-0.000000;,
  0.000000;-0.125108;-0.992143;,
  -0.188896;-0.981997;0.000000;,
  0.993903;-0.110256;-0.000000;,
  0.992144;-0.125103;-0.000000;,
  -0.993785;-0.111316;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.188902;-0.981996;-0.000000;,
  0.063393;-0.997989;-0.000000;,
  -0.190696;-0.981649;0.000000;,
  0.993785;-0.111319;-0.000000;,
  -0.993903;-0.110256;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.211667;0.977342;,
  0.000000;-0.259282;0.965802;,
  -0.981090;-0.193551;0.000000;,
  0.000000;-0.192478;0.981301;,
  -0.965036;-0.262117;0.000000;,
  -0.976998;-0.213249;0.000000;,
  0.000000;-1.000000;0.000914;,
  0.000000;-0.982046;-0.188641;,
  0.000000;-0.982046;-0.188641;,
  -0.063389;-0.997989;0.000000;,
  0.000000;-0.981700;0.190437;,
  0.000000;-0.981699;0.190437;,
  0.000000;-0.055659;-0.998450;,
  0.000000;-0.166458;-0.986049;,
  0.000000;-0.111318;-0.993785;,
  0.000000;-0.166458;-0.986049;,
  0.999146;-0.041326;-0.000000;,
  0.986314;-0.164880;-0.000000;,
  -0.000000;-0.164901;0.986310;,
  0.000000;-0.164901;0.986310;,
  0.000000;-0.110270;0.993902;,
  0.000000;-0.055135;0.998479;,
  -0.999129;-0.041723;0.000000;,
  -0.986049;-0.166455;0.000000;,
  -0.986049;-0.166455;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.809015;0.000000;-0.587788;,
  0.309017;0.000000;-0.951056;,
  0.994186;0.000000;0.107677;,
  -0.065216;-0.997871;0.000000;,
  -0.000001;-0.997874;-0.065165;,
  0.000000;-0.997952;0.063970;,
  0.000000;-0.981850;0.189659;,
  0.000000;-0.981850;0.189659;,
  0.809014;0.000000;0.587789;,
  0.999129;-0.041724;-0.000000;,
  0.986048;-0.166460;-0.000000;,
  0.000000;-0.163932;-0.986472;,
  0.000000;-0.163932;-0.986472;,
  0.000000;-0.109618;-0.993974;,
  0.000000;-0.054809;-0.998497;,
  -0.986314;-0.164881;0.000000;,
  -0.986314;-0.164881;0.000000;,
  -0.999146;-0.041326;0.000000;,
  0.000000;-0.055345;0.998467;,
  0.000000;-0.165527;0.986205;,
  0.000000;-0.110691;0.993855;,
  -0.121323;-0.000000;-0.992613;,
  -0.809019;-0.000000;-0.587783;,
  0.121322;0.000000;0.992613;,
  0.000000;-0.226013;0.974124;,
  -0.965036;-0.262117;0.000000;,
  0.000000;-0.259282;0.965802;,
  -0.973667;-0.227975;0.000000;,
  0.000000;-0.125087;0.992146;,
  0.000000;-0.125087;0.992146;,
  -0.992236;-0.124369;0.000000;,
  -0.992236;-0.124369;0.000000;,
  0.000000;-0.125087;0.992146;,
  -0.992236;-0.124369;0.000000;,
  -0.992236;-0.124369;0.000000;,
  -0.809018;-0.000000;0.587784;,
  -0.309013;-0.000000;0.951058;,
  -0.000001;-0.981555;-0.191178;,
  -0.000002;-0.981491;-0.191509;,
  0.000000;-0.981483;-0.191551;,
  -0.997895;-0.000000;0.064844;,
  -0.997895;0.000000;-0.064847;,
  -1.000000;-0.000000;-0.000002;,
  -0.994186;-0.000000;-0.107675;,
  -1.000000;0.000000;-0.000002;,
  -0.997895;-0.000000;0.064843;,
  0.000007;-0.000000;1.000000;,
  0.000013;-0.000000;1.000000;,
  0.000001;-0.000001;1.000000;,
  -0.000000;-0.000001;1.000000;,
  -0.000001;-0.000000;1.000000;,
  -0.000001;-0.000001;1.000000;;
  382;
  3;0,1,2;,
  3;1,3,2;,
  3;4,0,2;,
  3;3,5,2;,
  3;6,4,2;,
  3;5,7,2;,
  3;8,6,2;,
  3;7,9,2;,
  3;10,8,2;,
  3;9,10,2;,
  3;1,0,12;,
  3;12,0,11;,
  3;12,13,1;,
  3;1,13,3;,
  3;14,11,4;,
  3;4,11,0;,
  3;11,15,12;,
  3;12,15,16;,
  3;16,17,12;,
  3;12,17,13;,
  3;13,18,3;,
  3;3,18,5;,
  3;19,15,14;,
  3;14,15,11;,
  3;4,6,14;,
  3;14,6,20;,
  3;17,21,13;,
  3;13,21,18;,
  3;7,5,22;,
  3;22,5,18;,
  3;23,20,8;,
  3;8,20,6;,
  3;20,24,14;,
  3;14,24,19;,
  3;22,25,7;,
  3;7,25,9;,
  3;26,23,10;,
  3;10,23,8;,
  3;18,21,22;,
  3;22,21,27;,
  3;10,9,26;,
  3;26,9,25;,
  3;28,24,23;,
  3;23,24,20;,
  3;27,29,22;,
  3;22,29,25;,
  3;30,28,26;,
  3;26,28,23;,
  3;25,29,26;,
  3;26,29,30;,
  3;33,31,32;,
  3;32,31,40;,
  3;36,34,35;,
  3;35,34,42;,
  3;33,32,37;,
  3;37,32,43;,
  3;36,38,34;,
  3;34,38,44;,
  3;39,40,31;,
  3;41,35,42;,
  3;45,37,43;,
  3;46,44,38;,
  3;47,47,47;,
  3;47,47,47;,
  3;15,48,16;,
  3;16,48,49;,
  3;49,50,16;,
  3;16,50,17;,
  3;51,51,51;,
  3;51,51,51;,
  3;50,52,17;,
  3;17,52,21;,
  3;55,53,54;,
  3;54,53,62;,
  3;55,54,56;,
  3;56,54,61;,
  3;59,57,58;,
  3;58,57,66;,
  3;59,60,57;,
  3;57,60,68;,
  3;61,62,53;,
  3;24,63,19;,
  3;19,63,64;,
  3;65,58,66;,
  3;67,56,61;,
  3;66,68,60;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;21,52,27;,
  3;27,52,70;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;29,71,30;,
  3;30,71,72;,
  3;73,74,39;,
  3;39,74,40;,
  3;41,42,76;,
  3;76,42,75;,
  3;32,40,77;,
  3;77,40,74;,
  3;75,42,76;,
  3;76,42,34;,
  3;78,43,77;,
  3;77,43,32;,
  3;34,44,76;,
  3;76,44,79;,
  3;45,43,80;,
  3;80,43,78;,
  3;81,79,46;,
  3;46,79,44;,
  3;82,74,82;,
  3;82,74,73;,
  3;76,75,83;,
  3;83,75,83;,
  3;107,84,108;,
  3;108,84,109;,
  3;110,85,86;,
  3;86,85,85;,
  3;77,74,82;,
  3;82,74,82;,
  3;83,75,87;,
  3;87,75,76;,
  3;107,111,84;,
  3;84,111,112;,
  3;88,110,88;,
  3;88,110,86;,
  3;82,78,82;,
  3;82,78,77;,
  3;76,79,87;,
  3;87,79,87;,
  3;113,114,115;,
  3;115,114,116;,
  3;117,89,118;,
  3;118,89,118;,
  3;80,78,90;,
  3;90,78,82;,
  3;87,79,83;,
  3;83,79,81;,
  3;119,120,121;,
  3;121,120,122;,
  3;123,124,91;,
  3;91,124,125;,
  3;92,113,92;,
  3;92,113,115;,
  3;121,122,93;,
  3;93,122,93;,
  3;99,92,92;,
  3;92,92,92;,
  3;51,51,51;,
  3;51,51,51;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;93,93,93;,
  3;93,93,100;,
  3;47,47,47;,
  3;47,47,47;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,126;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,127;,
  3;49,48,128;,
  3;128,48,129;,
  3;130,50,128;,
  3;128,50,49;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;94,94,95;,
  3;95,94,131;,
  3;95,131,96;,
  3;96,131,96;,
  3;51,51,51;,
  3;51,51,51;,
  3;132,133,134;,
  3;134,133,135;,
  3;136,52,130;,
  3;130,52,50;,
  3;51,51,51;,
  3;51,51,51;,
  3;137,138,97;,
  3;97,138,138;,
  3;139,140,141;,
  3;141,140,142;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;143,144,98;,
  3;98,144,145;,
  3;51,51,51;,
  3;51,51,51;,
  3;146,147,148;,
  3;148,147,147;,
  3;51,51,51;,
  3;51,51,51;,
  3;64,63,149;,
  3;149,63,150;,
  3;141,142,92;,
  3;92,142,92;,
  3;93,146,93;,
  3;93,146,148;,
  3;70,52,151;,
  3;151,52,136;,
  3;51,51,51;,
  3;51,51,51;,
  3;92,92,92;,
  3;92,92,99;,
  3;47,47,47;,
  3;47,47,47;,
  3;69,69,69;,
  3;69,69,69;,
  3;100,93,93;,
  3;93,93,93;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;152,101,61;,
  3;61,101,62;,
  3;69,69,69;,
  3;69,69,69;,
  3;54,62,102;,
  3;102,62,101;,
  3;69,69,69;,
  3;69,69,69;,
  3;65,66,153;,
  3;153,66,103;,
  3;104,61,102;,
  3;102,61,54;,
  3;69,69,69;,
  3;69,69,69;,
  3;103,66,105;,
  3;105,66,57;,
  3;67,61,154;,
  3;154,61,104;,
  3;57,68,105;,
  3;105,68,106;,
  3;155,106,66;,
  3;66,106,68;,
  3;156,101,157;,
  3;157,101,152;,
  3;102,101,157;,
  3;157,101,156;,
  3;153,103,158;,
  3;158,103,159;,
  3;160,104,157;,
  3;157,104,102;,
  3;159,103,161;,
  3;161,103,105;,
  3;154,104,156;,
  3;156,104,160;,
  3;105,106,161;,
  3;161,106,162;,
  3;72,71,163;,
  3;163,71,164;,
  3;162,106,162;,
  3;162,106,155;,
  3;51,51,117;,
  3;51,51,117;,
  3;89,117,51;,
  3;47,123,47;,
  3;47,123,47;,
  3;123,91,47;,
  3;133,132,165;,
  3;132,166,165;,
  3;166,167,165;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,137,51;,
  3;51,137,51;,
  3;137,97,51;,
  3;47,47,145;,
  3;47,47,145;,
  3;98,145,47;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;168,63,169;,
  3;63,24,169;,
  3;169,24,170;,
  3;24,28,170;,
  3;72,168,30;,
  3;168,169,30;,
  3;169,170,30;,
  3;170,28,30;,
  3;150,63,171;,
  3;168,172,63;,
  3;172,173,63;,
  3;63,173,171;,
  3;171,173,163;,
  3;168,72,172;,
  3;172,72,173;,
  3;173,72,163;,
  3;64,92,19;,
  3;92,92,19;,
  3;92,92,19;,
  3;92,92,19;,
  3;92,48,92;,
  3;48,15,92;,
  3;92,15,92;,
  3;92,15,92;,
  3;92,15,19;,
  3;70,174,27;,
  3;174,175,27;,
  3;175,176,27;,
  3;176,177,27;,
  3;93,71,178;,
  3;71,29,178;,
  3;178,29,179;,
  3;179,29,177;,
  3;177,29,27;,
  3;129,48,149;,
  3;92,92,48;,
  3;92,64,92;,
  3;64,149,92;,
  3;92,149,92;,
  3;92,149,92;,
  3;92,149,92;,
  3;92,149,92;,
  3;92,149,92;,
  3;92,92,48;,
  3;48,92,149;,
  3;164,71,151;,
  3;93,93,71;,
  3;174,70,93;,
  3;70,151,93;,
  3;93,151,93;,
  3;93,151,93;,
  3;93,151,93;,
  3;93,151,93;,
  3;93,151,93;,
  3;93,93,71;,
  3;71,93,151;;
 }
 MeshTextureCoords {
  287;
  0.475858;0.914926;,
  0.436796;0.886546;,
  0.500000;0.837500;,
  0.421875;0.840625;,
  0.524142;0.914926;,
  0.436796;0.794704;,
  0.563204;0.886546;,
  0.475858;0.766324;,
  0.578125;0.840625;,
  0.524142;0.766324;,
  0.563204;0.794704;,
  0.405039;0.911188;,
  0.463728;0.953828;,
  0.382622;0.842195;,
  0.536272;0.953828;,
  0.451716;0.992353;,
  0.373591;0.935591;,
  0.343750;0.843750;,
  0.405039;0.773202;,
  0.548284;0.992353;,
  0.594961;0.911188;,
  0.373591;0.751909;,
  0.463728;0.730562;,
  0.617378;0.842195;,
  0.626409;0.935591;,
  0.536272;0.730562;,
  0.594961;0.773202;,
  0.451716;0.695147;,
  0.656250;0.843750;,
  0.548284;0.695147;,
  0.626409;0.751909;,
  0.499388;0.500000;,
  0.563404;0.500000;,
  0.499388;0.543574;,
  0.563404;0.543122;,
  0.499388;0.500000;,
  0.499388;0.543574;,
  0.435996;0.500000;,
  0.435996;0.543122;,
  0.435996;0.500000;,
  0.435996;0.543122;,
  0.563404;0.500000;,
  0.563404;0.543122;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.563404;0.250000;,
  0.563404;0.206878;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.435996;0.206878;,
  0.435996;0.250000;,
  0.425000;0.688440;,
  0.425000;0.400217;,
  0.450000;0.688440;,
  0.450000;0.400217;,
  0.475000;0.400217;,
  0.475000;0.688440;,
  0.375000;0.250000;,
  0.435996;0.206878;,
  0.435996;0.250000;,
  0.563404;0.250000;,
  0.563404;0.206878;,
  0.625000;0.250000;,
  0.500000;0.400217;,
  0.500000;0.688440;,
  0.499388;0.500000;,
  0.563404;0.500000;,
  0.499388;0.543574;,
  0.563404;0.543122;,
  0.435996;0.500000;,
  0.435996;0.543122;,
  0.499388;0.500000;,
  0.499388;0.543574;,
  0.435996;0.500000;,
  0.435996;0.543122;,
  0.563404;0.500000;,
  0.563404;0.543122;,
  0.625000;0.500000;,
  0.375000;0.688440;,
  0.375000;0.400217;,
  0.400000;0.688440;,
  0.400000;0.400217;,
  0.375000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.373591;0.064409;,
  0.451716;0.007647;,
  0.500000;0.150000;,
  0.343750;0.156250;,
  0.548284;0.007647;,
  0.525000;0.688440;,
  0.525000;0.400217;,
  0.373591;0.248091;,
  0.626409;0.064409;,
  0.451716;0.304853;,
  0.656250;0.156250;,
  0.548284;0.304853;,
  0.626409;0.248091;,
  0.550000;0.688440;,
  0.550000;0.400217;,
  0.575000;0.688440;,
  0.575000;0.400217;,
  0.625000;0.563198;,
  0.563404;0.563198;,
  0.375000;0.563198;,
  0.435996;0.563198;,
  0.499388;0.563198;,
  0.499388;0.563198;,
  0.435996;0.563198;,
  0.563404;0.563198;,
  0.375000;0.563198;,
  0.625000;0.563198;,
  0.563404;0.750000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.435996;0.750000;,
  0.499388;0.250000;,
  0.499388;0.250000;,
  0.435996;0.250000;,
  0.499388;0.750000;,
  0.499388;0.750000;,
  0.563404;0.250000;,
  0.435996;0.750000;,
  0.563404;0.750000;,
  0.375000;0.250000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.250000;,
  0.875000;0.186801;,
  0.875000;0.250000;,
  0.625000;0.186801;,
  0.125000;0.250000;,
  0.375000;0.186801;,
  0.125000;0.186801;,
  0.875000;0.000000;,
  0.625000;0.000000;,
  0.375000;0.186801;,
  0.125000;0.186801;,
  0.375000;0.000000;,
  0.125000;0.000000;,
  0.499388;0.206426;,
  0.375000;0.000000;,
  0.125000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.186801;,
  0.625000;0.000000;,
  0.625000;0.186801;,
  0.625000;1.000000;,
  0.563404;1.000000;,
  0.375000;1.000000;,
  0.435996;1.000000;,
  0.499388;1.000000;,
  0.499388;1.000000;,
  0.435996;1.000000;,
  0.563404;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.563404;0.186801;,
  0.499388;0.186801;,
  0.435996;0.186801;,
  0.563404;0.000000;,
  0.499388;0.000000;,
  0.435996;0.000000;,
  0.450000;0.312500;,
  0.425000;0.312500;,
  0.475000;0.312500;,
  0.494259;0.250000;,
  0.494259;0.206463;,
  0.499388;0.206426;,
  0.499388;0.250000;,
  0.375000;0.186801;,
  0.435996;0.186801;,
  0.563404;0.250000;,
  0.499388;0.250000;,
  0.435996;0.250000;,
  0.563404;0.186801;,
  0.499388;0.186801;,
  0.500000;0.312500;,
  0.625000;0.186801;,
  0.625000;0.250000;,
  0.435996;0.000000;,
  0.375000;0.000000;,
  0.494259;0.186801;,
  0.494259;0.000000;,
  0.499388;0.000000;,
  0.375000;0.250000;,
  0.563404;0.000000;,
  0.625000;0.000000;,
  0.400000;0.312500;,
  0.375000;0.312500;,
  0.125000;0.250000;,
  0.125000;0.186801;,
  0.875000;0.186801;,
  0.875000;0.250000;,
  0.525000;0.312500;,
  0.875000;0.000000;,
  0.875000;0.186801;,
  0.625000;0.000000;,
  0.625000;0.186801;,
  0.125000;0.000000;,
  0.375000;0.186801;,
  0.125000;0.186801;,
  0.375000;0.000000;,
  0.125000;0.000000;,
  0.563404;1.000000;,
  0.563404;0.750000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.875000;0.000000;,
  0.499388;1.000000;,
  0.499388;0.750000;,
  0.375000;0.750000;,
  0.435996;0.750000;,
  0.375000;1.000000;,
  0.435996;1.000000;,
  0.435996;1.000000;,
  0.435996;0.750000;,
  0.625000;0.563198;,
  0.563404;0.563198;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.499388;0.563198;,
  0.499388;1.000000;,
  0.499388;0.750000;,
  0.563404;1.000000;,
  0.563404;0.750000;,
  0.375000;0.563198;,
  0.435996;0.563198;,
  0.435996;0.563198;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.499388;0.563198;,
  0.375000;0.563198;,
  0.563404;0.563198;,
  0.625000;0.563198;,
  0.575000;0.312500;,
  0.550000;0.312500;,
  0.125000;0.250000;,
  0.375000;0.205360;,
  0.875000;0.250000;,
  0.625000;0.205360;,
  0.494259;0.195844;,
  0.875000;0.250000;,
  0.625000;0.205360;,
  0.125000;0.250000;,
  0.375000;0.205360;,
  0.494259;1.000000;,
  0.600000;0.400217;,
  0.625000;0.400217;,
  0.600000;0.403468;,
  0.625000;0.688440;,
  0.600000;0.416802;,
  0.600000;0.688440;,
  0.625000;0.312500;,
  0.600000;0.312500;,
  0.600000;0.397447;,
  0.600000;0.385020;,
  0.407317;0.400217;,
  0.407317;0.404445;,
  0.409791;0.417302;,
  0.412361;0.417735;,
  0.417356;0.400216;,
  0.417356;0.404445;,
  0.414907;0.417302;,
  0.532644;0.400217;,
  0.532644;0.404445;,
  0.535117;0.417302;,
  0.537688;0.417735;,
  0.542683;0.400217;,
  0.542683;0.404445;,
  0.540234;0.417302;,
  0.417356;0.398459;,
  0.407317;0.398459;,
  0.407317;0.386104;,
  0.409791;0.386104;,
  0.412361;0.386104;,
  0.414907;0.386104;,
  0.417356;0.386104;,
  0.542683;0.398459;,
  0.532644;0.398459;,
  0.532644;0.386104;,
  0.535117;0.386104;,
  0.537688;0.386104;,
  0.540233;0.386104;,
  0.542683;0.386104;;
 }
}
