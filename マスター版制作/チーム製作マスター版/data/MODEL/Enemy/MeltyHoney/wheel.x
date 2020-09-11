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
 212;
 67.43540;-11.03110;-15.94640;,
 64.72000;-11.03110;-15.94640;,
 67.43540;-18.04235;-6.29635;,
 64.72000;-18.04235;-6.29635;,
 64.72000;-11.03110;-15.94640;,
 64.72000;0.31335;-0.33215;,
 64.72000;-18.04235;-6.29635;,
 63.70885;0.31335;-19.63240;,
 64.72000;-18.04235;5.63200;,
 64.72000;11.65780;-15.94640;,
 64.72000;-11.03110;15.28215;,
 64.72000;18.66900;-6.29635;,
 64.72000;0.31335;18.96820;,
 64.72000;18.66900;5.63200;,
 64.72000;11.65780;15.28215;,
 64.72000;11.65780;15.28215;,
 67.43540;11.65780;15.28215;,
 64.72000;0.31335;18.96820;,
 67.43540;0.31335;18.96820;,
 64.72000;18.66900;5.63200;,
 67.43540;18.66900;5.63200;,
 64.72000;11.65780;15.28215;,
 67.43540;11.65780;15.28215;,
 67.43540;-11.03110;-15.94640;,
 67.43540;-12.92345;-18.55105;,
 67.43540;0.31335;-22.85190;,
 67.43540;0.31335;-19.63240;,
 67.43540;-12.92345;-18.55105;,
 67.43540;-21.10425;-7.29115;,
 35.39100;-21.10425;-7.29115;,
 35.39100;-12.92345;-18.55105;,
 67.43540;0.31335;-22.85190;,
 35.39100;0.31335;-22.85190;,
 67.43540;13.55010;-18.55105;,
 67.43540;11.65780;-15.94640;,
 67.43540;-21.10425;6.62685;,
 35.39100;-21.10425;6.62685;,
 67.43540;-11.03110;15.28215;,
 67.43540;-18.04235;5.63200;,
 64.72000;-18.04235;5.63200;,
 64.72000;-11.03110;15.28215;,
 -63.71315;-11.03110;-15.94640;,
 -67.43965;-11.03110;-15.94640;,
 -63.71315;-18.04235;-6.29635;,
 -67.43965;-18.04235;-6.29635;,
 67.43540;13.55010;-18.55105;,
 35.39100;13.55010;-18.55105;,
 -63.71315;-11.03110;-15.94640;,
 -63.71315;-18.04235;-6.29635;,
 -63.71315;0.31335;-0.33210;,
 -63.71315;0.31335;-19.63240;,
 -63.71315;-18.04235;5.63200;,
 35.39100;0.31335;-13.38585;,
 35.39100;0.31335;-22.85190;,
 35.39100;-12.92345;-18.55105;,
 35.39100;-7.35955;-10.89280;,
 -63.71315;11.65780;-15.94640;,
 67.43540;-12.92345;17.88680;,
 35.39100;-12.92345;17.88680;,
 -63.71315;-11.03110;15.28215;,
 67.43540;0.31335;18.96820;,
 67.43540;0.31335;22.18770;,
 67.43540;-12.92345;17.88680;,
 67.43540;-11.03110;15.28215;,
 -63.71315;18.66900;-6.29635;,
 67.43540;-21.10425;-7.29115;,
 67.43540;-18.04235;-6.29635;,
 -63.71315;0.31335;18.96820;,
 35.39100;7.98610;-10.89280;,
 35.39100;13.55010;-18.55105;,
 67.43540;21.73090;-7.29115;,
 35.39100;21.73090;-7.29115;,
 -63.71315;18.66900;5.63200;,
 67.43540;18.66900;-6.29635;,
 64.72000;18.66900;-6.29635;,
 -63.71315;11.65780;15.28215;,
 67.43540;0.31335;-19.63240;,
 63.70885;0.31335;-19.63240;,
 -67.43965;11.65780;15.28215;,
 -63.71315;11.65780;15.28215;,
 -67.43965;0.31335;18.96820;,
 -63.71315;0.31335;18.96820;,
 67.43540;11.65780;15.28215;,
 67.43540;13.55010;17.88680;,
 67.43540;-21.10425;6.62685;,
 67.43540;-18.04235;5.63200;,
 -67.43965;18.66900;5.63200;,
 -63.71315;18.66900;5.63200;,
 -67.43965;11.65780;15.28215;,
 -63.71315;11.65780;15.28215;,
 67.43540;0.31335;22.18770;,
 35.39100;0.31335;22.18770;,
 67.43540;21.73090;6.62685;,
 35.39100;21.73090;6.62685;,
 35.39100;-7.35955;10.22865;,
 35.39100;-12.92345;17.88680;,
 35.39100;0.31335;22.18770;,
 35.39100;0.31335;12.72165;,
 35.39100;-12.10160;3.70180;,
 -35.56640;-12.10160;3.70180;,
 -35.56640;-12.10160;-4.36600;,
 35.39100;-12.10160;-4.36600;,
 67.43540;13.55010;17.88680;,
 35.39100;13.55010;17.88680;,
 67.43540;13.55010;17.88680;,
 35.39100;13.55010;17.88680;,
 67.43540;11.65780;-15.94640;,
 64.72000;11.65780;-15.94640;,
 35.39100;13.55010;17.88680;,
 35.39100;7.98610;10.22865;,
 -35.56640;-7.35955;-10.89280;,
 -35.56640;-12.92345;-18.55105;,
 -35.56645;0.31335;-22.85190;,
 -35.56640;0.31335;-13.38585;,
 -67.43965;-12.92345;-18.55105;,
 -35.56640;-12.92345;-18.55105;,
 -35.56640;-21.10425;-7.29115;,
 -67.43965;-21.10425;-7.29115;,
 67.43540;21.73090;-7.29115;,
 67.43540;18.66900;-6.29635;,
 -67.43965;0.31335;-22.85190;,
 -35.56645;0.31335;-22.85190;,
 35.39100;12.72820;-4.36600;,
 -35.56640;12.72820;-4.36600;,
 -35.56640;12.72820;3.70180;,
 35.39100;12.72820;3.70180;,
 -35.56640;13.55010;-18.55105;,
 -35.56640;7.98610;-10.89280;,
 35.39100;-21.10425;-7.29115;,
 35.39100;-12.10160;-4.36600;,
 -35.56640;-21.10425;6.62685;,
 -67.43965;-21.10425;6.62685;,
 -67.43965;13.55010;-18.55105;,
 -35.56640;13.55010;-18.55105;,
 -67.43965;-11.03110;-15.94640;,
 -67.43965;0.31335;-19.63240;,
 -67.43965;0.31335;-22.85190;,
 -67.43965;-12.92345;-18.55105;,
 -35.56640;-12.92345;17.88680;,
 -67.43965;-12.92345;17.88680;,
 -35.56640;0.31335;12.72165;,
 -35.56640;0.31335;22.18770;,
 -35.56640;-12.92345;17.88680;,
 -35.56640;-7.35955;10.22865;,
 -67.43965;11.65780;-15.94640;,
 -67.43965;13.55010;-18.55105;,
 -67.43965;21.73090;-7.29115;,
 -35.56640;21.73090;-7.29115;,
 35.39100;-12.10160;3.70180;,
 35.39100;-21.10425;6.62685;,
 -35.56640;7.98610;10.22865;,
 -35.56640;13.55010;17.88680;,
 -67.43965;-11.03110;15.28215;,
 -63.71315;-11.03110;15.28215;,
 -63.71315;-18.04235;5.63200;,
 -67.43965;-18.04235;5.63200;,
 67.43540;18.66900;5.63200;,
 67.43540;21.73090;6.62685;,
 -35.56640;0.31335;22.18770;,
 -67.43965;0.31335;22.18770;,
 35.39100;21.73090;-7.29115;,
 35.39100;12.72820;-4.36600;,
 -67.43965;21.73090;6.62685;,
 -35.56640;21.73090;6.62685;,
 -67.43965;0.31335;18.96820;,
 -67.43965;-11.03110;15.28215;,
 -67.43965;-12.92345;17.88680;,
 -67.43965;0.31335;22.18770;,
 -35.56640;13.55010;17.88680;,
 -67.43965;13.55010;17.88680;,
 -67.43965;13.55010;17.88680;,
 -35.56640;13.55010;17.88680;,
 -67.43965;18.66900;-6.29635;,
 -63.71315;18.66900;-6.29635;,
 -67.43965;11.65780;15.28215;,
 -67.43965;13.55010;17.88680;,
 35.39100;12.72820;3.70180;,
 35.39100;21.73090;6.62685;,
 -35.56640;-21.10425;-7.29115;,
 -35.56640;-12.10160;-4.36600;,
 -35.56640;-12.10160;3.70180;,
 -35.56640;-21.10425;6.62685;,
 -67.43965;-21.10425;-7.29115;,
 -67.43965;-18.04235;-6.29635;,
 -35.56640;21.73090;-7.29115;,
 -35.56640;12.72820;-4.36600;,
 -63.71315;0.31335;-19.63240;,
 -67.43965;0.31335;-19.63240;,
 -67.43965;-21.10425;6.62685;,
 -67.43965;-18.04235;5.63200;,
 -63.71315;11.65780;-15.94640;,
 -67.43965;11.65780;-15.94640;,
 -35.56640;-7.35955;-10.89280;,
 35.39100;-7.35955;-10.89280;,
 -35.56640;0.31335;-13.38585;,
 35.39100;0.31335;-13.38585;,
 -35.56640;12.72820;3.70180;,
 -35.56640;21.73090;6.62685;,
 -67.43965;21.73090;-7.29115;,
 -67.43965;18.66900;-6.29635;,
 -35.56640;7.98610;-10.89280;,
 35.39100;7.98610;-10.89280;,
 35.39100;-7.35955;10.22865;,
 -35.56640;-7.35955;10.22865;,
 35.39100;0.31335;12.72165;,
 -35.56640;0.31335;12.72165;,
 -67.43965;18.66900;5.63200;,
 -67.43965;21.73090;6.62685;,
 35.39100;7.98610;10.22865;,
 -35.56640;7.98610;10.22865;,
 35.39100;7.98610;10.22865;,
 -35.56640;7.98610;10.22865;;
 
 158;
 3;0,1,2;,
 3;1,3,2;,
 3;4,5,6;,
 3;7,5,4;,
 3;6,5,8;,
 3;9,5,7;,
 3;8,5,10;,
 3;11,5,9;,
 3;10,5,12;,
 3;13,5,11;,
 3;12,5,14;,
 3;14,5,13;,
 3;15,16,17;,
 3;16,18,17;,
 3;19,20,21;,
 3;20,22,21;,
 4;23,24,25,26;,
 4;27,28,29,30;,
 4;31,27,30,32;,
 4;26,25,33,34;,
 4;28,35,36,29;,
 4;37,38,39,40;,
 3;41,42,43;,
 3;42,44,43;,
 4;45,31,32,46;,
 3;47,48,49;,
 3;50,47,49;,
 3;48,51,49;,
 4;52,53,54,55;,
 3;56,50,49;,
 4;35,57,58,36;,
 3;51,59,49;,
 4;60,61,62,63;,
 3;64,56,49;,
 3;24,23,65;,
 3;23,66,65;,
 3;59,67,49;,
 4;68,69,53,52;,
 4;70,45,46,71;,
 3;72,64,49;,
 4;73,20,19,74;,
 3;67,75,49;,
 3;75,72,49;,
 3;76,77,0;,
 3;77,1,0;,
 3;78,79,80;,
 3;79,81,80;,
 4;82,83,61,60;,
 3;65,66,84;,
 3;66,85,84;,
 3;86,87,88;,
 3;87,89,88;,
 4;57,90,91,58;,
 3;2,3,38;,
 3;3,39,38;,
 4;92,70,71,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;90,102,103,91;,
 4;104,92,93,105;,
 3;76,106,77;,
 3;77,106,107;,
 4;97,96,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 3;33,118,34;,
 3;34,118,119;,
 4;120,121,115,114;,
 4;122,123,124,125;,
 4;113,112,126,127;,
 3;54,128,55;,
 3;55,128,129;,
 3;106,73,107;,
 3;107,73,74;,
 4;117,116,130,131;,
 3;40,17,37;,
 3;37,17,18;,
 4;132,133,121,120;,
 4;134,135,136,137;,
 4;131,130,138,139;,
 4;140,141,142,143;,
 4;135,144,145,136;,
 4;146,147,133,132;,
 3;148,149,94;,
 3;149,95,94;,
 4;150,151,141,140;,
 4;152,153,154,155;,
 3;156,157,82;,
 3;157,83,82;,
 4;139,138,158,159;,
 3;69,68,160;,
 3;68,161,160;,
 4;162,163,147,146;,
 4;164,165,166,167;,
 4;159,158,168,169;,
 3;85,63,84;,
 3;84,63,62;,
 4;170,171,163,162;,
 4;172,173,87,86;,
 4;174,164,167,175;,
 3;176,109,177;,
 3;177,109,108;,
 3;111,110,178;,
 3;110,179,178;,
 3;128,149,129;,
 3;129,149,148;,
 3;118,157,119;,
 3;119,157,156;,
 3;180,143,181;,
 3;181,143,142;,
 3;137,182,134;,
 3;134,182,183;,
 3;126,184,127;,
 3;127,184,185;,
 3;186,187,41;,
 3;187,42,41;,
 3;182,188,183;,
 3;183,188,189;,
 3;43,44,154;,
 3;44,155,154;,
 3;186,190,187;,
 3;187,190,191;,
 3;192,193,100;,
 3;100,193,101;,
 3;194,195,192;,
 3;192,195,193;,
 3;196,197,150;,
 3;197,151,150;,
 3;145,144,198;,
 3;144,199,198;,
 3;160,161,177;,
 3;161,176,177;,
 3;190,173,191;,
 3;191,173,172;,
 3;194,200,195;,
 3;200,201,195;,
 3;152,80,153;,
 3;80,81,153;,
 3;98,202,99;,
 3;202,203,99;,
 3;200,123,201;,
 3;123,122,201;,
 3;202,204,203;,
 3;204,205,203;,
 3;206,174,207;,
 3;207,174,175;,
 3;178,179,181;,
 3;179,180,181;,
 3;208,209,204;,
 3;204,209,205;,
 3;125,124,210;,
 3;210,124,211;,
 3;184,197,185;,
 3;185,197,196;,
 3;189,188,165;,
 3;188,166,165;,
 3;198,199,207;,
 3;199,206,207;;
 
 MeshMaterialList {
  2;
  158;
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
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
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
  0,
  0,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
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
  0;;
  Material {
   0.138400;0.138400;0.138400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.332800;0.332800;0.332800;1.000000;;
   5.000000;
   0.300000;0.300000;0.300000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  73;
  0.000000;0.912252;0.409630;,
  0.000000;0.497252;0.867606;,
  0.000000;0.978801;0.204815;,
  0.000000;0.671477;0.741026;,
  0.999946;-0.000000;-0.010444;,
  0.998630;-0.000000;-0.052319;,
  1.000000;0.000000;0.000000;,
  0.999012;-0.035948;-0.026118;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.497257;-0.867603;,
  0.000000;-0.912254;-0.409625;,
  0.000000;-0.951057;-0.309017;,
  0.000000;-0.587784;-0.809018;,
  0.000000;0.000001;-1.000000;,
  0.000000;-0.951057;0.309016;,
  0.000000;0.497256;-0.867604;,
  0.000000;0.978801;-0.204814;,
  0.000000;0.912252;0.409630;,
  0.000000;0.497252;0.867606;,
  0.000000;0.978801;0.204815;,
  0.000000;0.587784;-0.809018;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.587786;0.809016;,
  0.000000;0.951057;-0.309017;,
  0.000000;-0.912252;0.409628;,
  0.000000;-0.671482;-0.741021;,
  0.000000;-0.951057;-0.309016;,
  0.000000;0.000001;1.000000;,
  0.000000;0.951057;0.309016;,
  0.000000;-0.951056;0.309018;,
  0.000000;-0.912253;0.409628;,
  0.000000;-0.912252;-0.409630;,
  0.000000;-0.951056;-0.309019;,
  0.000000;0.587787;0.809016;,
  1.000000;0.000000;-0.000001;,
  1.000000;0.000000;-0.000002;,
  1.000000;0.000000;-0.000004;,
  0.000000;0.000001;-1.000000;,
  0.000000;0.951055;-0.309022;,
  0.000000;0.912250;-0.409633;,
  0.000000;0.912251;0.409631;,
  0.000000;0.951056;0.309020;,
  1.000000;-0.000000;-0.000002;,
  1.000000;-0.000000;-0.000001;,
  0.000000;-0.951057;0.309016;,
  0.000000;-0.587786;0.809016;,
  0.000000;0.587786;-0.809017;,
  0.000000;0.951056;-0.309017;,
  0.000000;0.000001;1.000000;,
  0.000000;0.951057;0.309016;,
  0.000000;-0.951056;0.309018;,
  0.999012;0.035948;-0.026118;,
  0.000000;0.951056;-0.309017;,
  0.000000;-0.951056;0.309018;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.497253;0.867605;,
  0.000000;-0.671479;0.741024;,
  0.000000;0.497256;-0.867604;,
  0.000000;0.978801;-0.204814;,
  0.000000;-0.912253;0.409628;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.671479;0.741024;,
  0.000000;-0.497252;-0.867606;,
  0.000000;-0.671477;-0.741025;,
  0.000000;0.000003;-1.000000;,
  0.000000;0.497254;-0.867605;,
  0.000000;0.671476;-0.741027;,
  0.000000;-0.671477;0.741025;,
  0.000000;-0.497250;0.867607;,
  0.000000;0.000003;1.000000;,
  0.000000;0.671476;0.741026;,
  0.000000;0.497252;0.867606;;
  158;
  3;1,3,0;,
  3;3,2,0;,
  3;51,4,6;,
  3;5,4,51;,
  3;6,4,6;,
  3;7,4,5;,
  3;6,4,6;,
  3;6,4,7;,
  3;6,4,6;,
  3;6,4,6;,
  3;6,4,6;,
  3;6,4,6;,
  3;25,9,8;,
  3;9,8,8;,
  3;26,10,25;,
  3;10,9,25;,
  4;6,6,6,6;,
  4;12,11,11,12;,
  4;13,12,12,13;,
  4;6,6,6,6;,
  4;11,14,14,11;,
  4;15,16,52,46;,
  3;18,3,17;,
  3;3,19,17;,
  4;20,13,13,20;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  4;21,21,21,21;,
  3;21,21,21;,
  4;14,22,22,14;,
  3;21,21,21;,
  4;6,6,6,6;,
  3;21,21,21;,
  3;6,6,6;,
  3;6,6,6;,
  3;21,21,21;,
  4;21,21,21,21;,
  4;23,20,20,23;,
  3;21,21,21;,
  4;24,10,26,53;,
  3;21,21,21;,
  3;21,21,21;,
  3;54,55,1;,
  3;55,3,1;,
  3;25,9,8;,
  3;9,8,8;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;26,10,25;,
  3;10,9,25;,
  4;22,27,27,22;,
  3;0,2,16;,
  3;2,52,16;,
  4;28,23,23,28;,
  4;21,21,21,21;,
  4;29,30,31,32;,
  4;27,33,33,27;,
  4;33,28,28,33;,
  3;54,56,55;,
  3;55,56,57;,
  4;21,21,21,21;,
  4;34,35,36,36;,
  4;12,12,11,11;,
  3;6,6,6;,
  3;6,6,6;,
  4;37,37,12,12;,
  4;38,39,40,41;,
  4;36,36,42,43;,
  3;21,21,21;,
  3;21,21,21;,
  3;56,24,57;,
  3;57,24,53;,
  4;11,11,44,44;,
  3;46,8,15;,
  3;15,8,8;,
  4;20,20,37,37;,
  4;21,21,21,21;,
  4;44,44,45,45;,
  4;6,6,6,6;,
  4;21,21,21,21;,
  4;23,23,20,20;,
  3;21,21,21;,
  3;21,21,21;,
  4;6,6,6,6;,
  4;46,58,59,47;,
  3;6,6,6;,
  3;6,6,6;,
  4;45,45,48,48;,
  3;21,21,21;,
  3;21,21,21;,
  4;49,49,23,23;,
  4;21,21,21,21;,
  4;48,48,33,33;,
  3;6,6,6;,
  3;6,6,6;,
  4;33,33,49,49;,
  4;50,60,10,26;,
  4;21,21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;35,34,6;,
  3;34,6,6;,
  3;21,21,21;,
  3;21,21,21;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;21,21,21;,
  3;21,21,21;,
  3;42,6,43;,
  3;43,6,6;,
  3;61,61,18;,
  3;61,3,18;,
  3;21,21,21;,
  3;21,21,21;,
  3;17,19,59;,
  3;19,47,59;,
  3;61,56,61;,
  3;61,56,62;,
  3;63,64,31;,
  3;31,64,32;,
  3;65,65,63;,
  3;63,65,64;,
  3;6,6,6;,
  3;6,6,6;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;56,60,62;,
  3;62,60,50;,
  3;65,66,65;,
  3;66,67,65;,
  3;46,8,58;,
  3;8,8,58;,
  3;29,68,30;,
  3;68,69,30;,
  3;66,39,67;,
  3;39,38,67;,
  3;68,70,69;,
  3;70,70,69;,
  3;21,21,21;,
  3;21,21,21;,
  3;6,6,6;,
  3;6,6,6;,
  3;71,72,70;,
  3;70,72,70;,
  3;41,40,71;,
  3;71,40,72;,
  3;6,6,6;,
  3;6,6,6;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;;
 }
 MeshTextureCoords {
  212;
  0.500000;0.643360;,
  0.500000;0.688440;,
  0.525000;0.643360;,
  0.525000;0.688440;,
  0.373590;0.751910;,
  0.500000;0.837500;,
  0.451720;0.695150;,
  0.343750;0.843750;,
  0.548280;0.695150;,
  0.373590;0.935590;,
  0.626410;0.751910;,
  0.451720;0.992350;,
  0.656250;0.843750;,
  0.548280;0.992350;,
  0.626410;0.935590;,
  0.625000;0.688440;,
  0.625000;0.643360;,
  0.600000;0.688440;,
  0.600000;0.643360;,
  0.400000;0.688440;,
  0.400000;0.643360;,
  0.375000;0.688440;,
  0.375000;0.643360;,
  0.391660;0.234070;,
  0.373590;0.248090;,
  0.343750;0.156250;,
  0.366090;0.155360;,
  0.500000;0.312500;,
  0.525000;0.312500;,
  0.525000;0.688440;,
  0.500000;0.688440;,
  0.475000;0.312500;,
  0.475000;0.688440;,
  0.373590;0.064410;,
  0.391660;0.076650;,
  0.550000;0.312500;,
  0.550000;0.688440;,
  0.575000;0.643360;,
  0.550000;0.643360;,
  0.550000;0.688440;,
  0.575000;0.688440;,
  0.500000;0.688440;,
  0.500000;0.643360;,
  0.525000;0.688440;,
  0.525000;0.643360;,
  0.450000;0.312500;,
  0.450000;0.688440;,
  0.373590;0.751910;,
  0.451720;0.695150;,
  0.500000;0.837500;,
  0.343750;0.843750;,
  0.548280;0.695150;,
  0.409430;0.841120;,
  0.343750;0.843750;,
  0.373590;0.751910;,
  0.426730;0.787890;,
  0.373590;0.935590;,
  0.575000;0.312500;,
  0.575000;0.688440;,
  0.626410;0.751910;,
  0.633910;0.155360;,
  0.656250;0.156250;,
  0.626410;0.248090;,
  0.608340;0.234070;,
  0.451720;0.992350;,
  0.451720;0.304850;,
  0.458620;0.282710;,
  0.656250;0.843750;,
  0.426730;0.894360;,
  0.373590;0.935590;,
  0.425000;0.312500;,
  0.425000;0.688440;,
  0.548280;0.992350;,
  0.425000;0.643360;,
  0.425000;0.688440;,
  0.626410;0.935590;,
  0.475000;0.643360;,
  0.475000;0.688440;,
  0.625000;0.643360;,
  0.625000;0.688440;,
  0.600000;0.643360;,
  0.600000;0.688440;,
  0.608340;0.076650;,
  0.626410;0.064410;,
  0.548280;0.304850;,
  0.541380;0.282710;,
  0.400000;0.643360;,
  0.400000;0.688440;,
  0.375000;0.643360;,
  0.375000;0.688440;,
  0.600000;0.312500;,
  0.600000;0.688440;,
  0.400000;0.312500;,
  0.400000;0.688440;,
  0.573270;0.787890;,
  0.626410;0.751910;,
  0.656250;0.843750;,
  0.590570;0.841120;,
  0.550000;0.388540;,
  0.550000;0.612400;,
  0.525000;0.612400;,
  0.525000;0.388540;,
  0.625000;0.312500;,
  0.625000;0.688440;,
  0.375000;0.312500;,
  0.375000;0.688440;,
  0.450000;0.643360;,
  0.450000;0.688440;,
  0.626410;0.935590;,
  0.573270;0.894360;,
  0.426730;0.787890;,
  0.373590;0.751910;,
  0.343750;0.843750;,
  0.409430;0.841120;,
  0.500000;0.312500;,
  0.500000;0.688440;,
  0.525000;0.688440;,
  0.525000;0.312500;,
  0.451720;0.007650;,
  0.458620;0.028000;,
  0.475000;0.312500;,
  0.475000;0.688440;,
  0.425000;0.388540;,
  0.425000;0.612400;,
  0.400000;0.612400;,
  0.400000;0.388540;,
  0.373590;0.935590;,
  0.426730;0.894360;,
  0.451720;0.695150;,
  0.472010;0.754980;,
  0.550000;0.688440;,
  0.550000;0.312500;,
  0.450000;0.312500;,
  0.450000;0.688440;,
  0.391660;0.234070;,
  0.366090;0.155360;,
  0.343750;0.156250;,
  0.373590;0.248090;,
  0.575000;0.688440;,
  0.575000;0.312500;,
  0.590570;0.841120;,
  0.656250;0.843750;,
  0.626410;0.751910;,
  0.573270;0.787890;,
  0.391660;0.076650;,
  0.373590;0.064410;,
  0.425000;0.312500;,
  0.425000;0.688440;,
  0.527990;0.754980;,
  0.548280;0.695150;,
  0.573270;0.894360;,
  0.626410;0.935590;,
  0.575000;0.643360;,
  0.575000;0.688440;,
  0.550000;0.688440;,
  0.550000;0.643360;,
  0.541380;0.028000;,
  0.548280;0.007650;,
  0.600000;0.688440;,
  0.600000;0.312500;,
  0.451720;0.992350;,
  0.472010;0.927260;,
  0.400000;0.312500;,
  0.400000;0.688440;,
  0.633910;0.155360;,
  0.608340;0.234070;,
  0.626410;0.248090;,
  0.656250;0.156250;,
  0.625000;0.688440;,
  0.625000;0.312500;,
  0.375000;0.312500;,
  0.375000;0.688440;,
  0.425000;0.643360;,
  0.425000;0.688440;,
  0.608340;0.076650;,
  0.626410;0.064410;,
  0.527990;0.927260;,
  0.548280;0.992350;,
  0.451720;0.695150;,
  0.472010;0.754980;,
  0.527990;0.754980;,
  0.548280;0.695150;,
  0.451720;0.304850;,
  0.458620;0.282710;,
  0.451720;0.992350;,
  0.472010;0.927260;,
  0.475000;0.688440;,
  0.475000;0.643360;,
  0.548280;0.304850;,
  0.541380;0.282710;,
  0.450000;0.688440;,
  0.450000;0.643360;,
  0.500000;0.612400;,
  0.500000;0.388540;,
  0.475000;0.612400;,
  0.475000;0.388540;,
  0.527990;0.927260;,
  0.548280;0.992350;,
  0.451720;0.007650;,
  0.458620;0.028000;,
  0.450000;0.612400;,
  0.450000;0.388540;,
  0.575000;0.388540;,
  0.575000;0.612400;,
  0.600000;0.388540;,
  0.600000;0.612400;,
  0.541380;0.028000;,
  0.548280;0.007650;,
  0.625000;0.388540;,
  0.625000;0.612400;,
  0.375000;0.388540;,
  0.375000;0.612400;;
 }
}
