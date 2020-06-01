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
 34;
 0.63038;20.15540;-3.96723;,
 0.63038;14.74898;-6.46344;,
 -4.35717;14.74898;-2.66356;,
 -3.05917;20.15540;-1.83895;,
 -3.26087;21.25751;2.78832;,
 0.63038;27.31819;0.99680;,
 -3.41896;20.15540;0.99680;,
 -5.47060;14.74898;5.92910;,
 0.63038;14.74898;8.44283;,
 0.63038;23.14845;3.43039;,
 0.63038;-1.50254;0.99680;,
 0.63038;6.49143;6.94158;,
 -2.85358;5.03172;5.90559;,
 -7.00088;14.74898;0.99680;,
 5.73484;15.50037;4.44776;,
 7.73626;14.74898;0.99680;,
 4.82993;20.15540;0.99680;,
 2.19527;23.06719;2.43658;,
 -3.23310;3.09482;-2.12246;,
 -2.98916;2.18758;0.99680;,
 3.49793;14.74898;-3.96723;,
 4.05227;17.28494;-2.77202;,
 4.02953;4.64298;0.99680;,
 4.04175;6.98599;-2.74615;,
 3.34257;7.98010;5.78949;,
 0.63038;8.52612;-5.64424;,
 4.43384;11.73470;-3.96723;,
 0.63038;11.73470;-7.69739;,
 -5.47060;11.73470;-3.96723;,
 -7.46046;11.73470;0.99680;,
 -5.47060;8.04042;7.30818;,
 0.63038;11.73470;8.44283;,
 4.49794;11.73470;6.17156;,
 8.73676;11.73470;0.99680;;
 
 40;
 4;0,1,2,3;,
 3;4,5,6;,
 4;7,8,9,4;,
 3;10,11,12;,
 4;6,13,7,4;,
 4;14,15,16,17;,
 3;5,3,6;,
 4;2,13,6,3;,
 3;18,10,19;,
 4;16,15,20,21;,
 3;22,10,23;,
 3;24,11,10;,
 4;17,9,8,14;,
 3;17,5,9;,
 3;21,5,16;,
 4;20,1,0,21;,
 3;5,0,3;,
 3;16,5,17;,
 3;21,0,5;,
 3;9,5,4;,
 3;25,10,18;,
 3;24,10,22;,
 3;10,12,19;,
 3;23,10,25;,
 4;26,27,1,20;,
 4;2,1,27,28;,
 4;28,29,13,2;,
 4;7,13,29,30;,
 4;30,31,8,7;,
 4;14,8,31,32;,
 4;32,33,15,14;,
 4;20,15,33,26;,
 4;23,25,27,26;,
 4;28,27,25,18;,
 4;18,19,29,28;,
 4;30,29,19,12;,
 4;11,31,30,12;,
 4;32,31,11,24;,
 4;24,22,33,32;,
 4;26,33,22,23;;
 
 MeshMaterialList {
  1;
  40;
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
  0;;
  Material {
   0.533333;0.687059;0.800000;0.890000;;
   11.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game314\\Documents\\Visual Studio 2015\\Projects\\C++3D2nd\\data\\Texture\\Ice.jpg";
   }
  }
 }
 MeshNormals {
  45;
  0.683079;-0.435830;-0.586050;,
  -0.738755;-0.524314;-0.423481;,
  0.683730;0.373469;-0.626924;,
  -0.720077;0.448100;-0.529807;,
  0.650787;0.452579;0.609629;,
  -0.887737;0.455058;-0.069615;,
  0.663840;-0.402340;0.630427;,
  -0.446650;-0.625136;0.640085;,
  0.883385;0.466271;-0.047134;,
  -0.882870;0.446271;-0.146231;,
  -0.812342;-0.582443;0.029332;,
  0.881941;-0.468916;0.047924;,
  0.166362;-0.485999;-0.857979;,
  0.488385;-0.549649;0.677766;,
  0.268208;-0.449241;0.852201;,
  0.081851;0.507137;0.857970;,
  -0.760234;0.526465;-0.380629;,
  -0.482085;0.408239;-0.775200;,
  0.688683;0.266540;-0.674294;,
  -0.521435;0.355444;-0.775735;,
  -0.710118;0.356297;-0.607276;,
  -0.942628;0.316609;-0.105885;,
  -0.724867;0.317896;0.611154;,
  0.106282;0.314853;0.943171;,
  0.694705;0.295885;0.655620;,
  0.937170;0.340631;-0.075382;,
  0.733226;-0.063590;-0.677005;,
  0.658397;-0.049258;-0.751057;,
  -0.766986;-0.013981;-0.641512;,
  -0.987083;-0.139106;-0.079474;,
  -0.676661;-0.218038;0.703271;,
  0.183838;-0.119347;0.975684;,
  0.686725;-0.101793;0.719754;,
  0.819884;-0.121328;0.559527;,
  -0.354227;0.479119;0.803099;,
  -0.708084;-0.694543;0.127387;,
  0.465856;-0.555964;-0.688391;,
  0.636968;0.447162;0.627948;,
  0.683640;0.449218;-0.575187;,
  0.614451;0.271381;-0.740812;,
  0.590569;0.378636;-0.712645;,
  -0.361287;0.470016;0.805330;,
  0.016153;-0.552051;-0.833654;,
  -0.513792;0.015062;-0.857782;,
  0.800395;-0.077336;-0.594464;;
  40;
  4;17,19,20,3;,
  3;5,16,9;,
  4;22,23,15,34;,
  3;13,14,7;,
  4;9,21,22,5;,
  4;24,25,8,4;,
  3;16,3,9;,
  4;20,21,9,3;,
  3;1,35,10;,
  4;8,25,18,2;,
  3;11,36,0;,
  3;6,14,13;,
  4;4,15,23,24;,
  3;4,37,15;,
  3;2,38,8;,
  4;18,39,40,2;,
  3;16,17,3;,
  3;8,37,4;,
  3;2,40,38;,
  3;15,41,34;,
  3;12,36,42;,
  3;6,13,11;,
  3;35,7,10;,
  3;0,36,12;,
  4;26,27,39,18;,
  4;20,19,43,28;,
  4;28,29,21,20;,
  4;22,21,29,30;,
  4;30,31,23,22;,
  4;24,23,31,32;,
  4;32,33,25,24;,
  4;18,25,44,26;,
  4;0,12,27,26;,
  4;28,43,12,1;,
  4;1,10,29,28;,
  4;30,29,10,7;,
  4;14,31,30,7;,
  4;32,31,14,6;,
  4;6,11,33,32;,
  4;26,44,11,0;;
 }
 MeshTextureCoords {
  34;
  0.506304;-0.336336;,
  0.506304;-0.282272;,
  0.456428;-0.282272;,
  0.469408;-0.336336;,
  0.467391;-0.347357;,
  0.506304;-0.407964;,
  0.465810;-0.336336;,
  0.445294;-0.282272;,
  0.506304;-0.282272;,
  0.506304;-0.366266;,
  0.506304;-0.119757;,
  0.506304;-0.199696;,
  0.471464;-0.185099;,
  0.429991;-0.282272;,
  0.557348;-0.289786;,
  0.577363;-0.282272;,
  0.548299;-0.336336;,
  0.521953;-0.365454;,
  0.467669;-0.165730;,
  0.470108;-0.156658;,
  0.534979;-0.282272;,
  0.540523;-0.307631;,
  0.540295;-0.181212;,
  0.540417;-0.204642;,
  0.533426;-0.214583;,
  0.506304;-0.220043;,
  0.544338;-0.252129;,
  0.506304;-0.252129;,
  0.445294;-0.252129;,
  0.425395;-0.252129;,
  0.445294;-0.215186;,
  0.506304;-0.252129;,
  0.544979;-0.252129;,
  0.587368;-0.252129;;
 }
}
