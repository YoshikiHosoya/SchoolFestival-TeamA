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
 70;
 28.08463;0.04926;-17.95768;,
 13.50966;0.04926;-30.58689;,
 28.08463;109.46077;-17.95767;,
 13.50966;109.46077;-30.58688;,
 -5.57957;0.04926;-33.33154;,
 -5.57957;109.46077;-33.33154;,
 -23.12214;0.04926;-25.32009;,
 -23.12214;109.46077;-25.32008;,
 -33.54873;0.04926;-9.09613;,
 -33.54873;109.46077;-9.09612;,
 -33.54873;0.04926;10.18935;,
 -33.54873;109.46077;10.18936;,
 -23.12214;0.04926;26.41334;,
 -23.12214;109.46077;26.41334;,
 -5.57957;0.04926;34.42486;,
 -5.57957;109.46077;34.42487;,
 13.50966;0.04926;31.68020;,
 13.50966;109.46077;31.68020;,
 28.08463;0.04926;19.05090;,
 28.08463;109.46077;19.05090;,
 33.51798;0.04926;0.54665;,
 33.51798;109.46077;0.54666;,
 28.08463;0.04926;-17.95768;,
 28.08463;109.46077;-17.95767;,
 13.50966;0.04926;-30.58689;,
 28.08463;0.04926;-17.95768;,
 -0.70854;0.04926;0.54665;,
 -5.57957;0.04926;-33.33154;,
 -23.12214;0.04926;-25.32009;,
 -33.54873;0.04926;-9.09613;,
 -33.54873;0.04926;10.18935;,
 -23.12214;0.04926;26.41334;,
 -5.57957;0.04926;34.42486;,
 13.50966;0.04926;31.68020;,
 28.08463;0.04926;19.05090;,
 33.51798;0.04926;0.54665;,
 -0.70854;48.06728;0.54666;,
 20.73881;48.06728;-13.23679;,
 9.88231;48.06728;-22.64404;,
 -4.33687;48.06716;-24.68846;,
 -17.40399;48.06728;-18.72092;,
 -25.17042;48.06728;-6.63601;,
 -25.17042;48.06728;7.72934;,
 -17.40399;48.06728;19.81413;,
 -4.33687;48.06728;25.78178;,
 9.88231;48.06728;23.73736;,
 20.73881;48.06728;14.33010;,
 24.78599;48.06728;0.54666;,
 28.08463;109.46077;-17.95767;,
 13.50966;109.46077;-30.58688;,
 20.73881;109.46077;-13.23679;,
 9.88231;109.46077;-22.64404;,
 -5.57957;109.46077;-33.33154;,
 -4.33687;109.46077;-24.68846;,
 -23.12214;109.46077;-25.32008;,
 -17.40399;109.46077;-18.72091;,
 -33.54873;109.46077;-9.09612;,
 -25.17042;109.46077;-6.63601;,
 -33.54873;109.46077;10.18936;,
 -25.17042;109.46077;7.72934;,
 -23.12214;109.46077;26.41334;,
 -17.40399;109.46077;19.81413;,
 -5.57957;109.46077;34.42487;,
 -4.33687;109.46077;25.78178;,
 13.50966;109.46077;31.68020;,
 9.88231;109.46077;23.73736;,
 28.08463;109.46077;19.05090;,
 20.73881;109.46077;14.33011;,
 33.51798;109.46077;0.54666;,
 24.78599;109.46077;0.54666;;
 
 88;
 3;0,1,2;,
 3;2,1,3;,
 3;1,4,3;,
 3;3,4,5;,
 3;4,6,5;,
 3;5,6,7;,
 3;6,8,7;,
 3;7,8,9;,
 3;8,10,9;,
 3;9,10,11;,
 3;10,12,11;,
 3;11,12,13;,
 3;12,14,13;,
 3;13,14,15;,
 3;14,16,15;,
 3;15,16,17;,
 3;16,18,17;,
 3;17,18,19;,
 3;18,20,19;,
 3;19,20,21;,
 3;20,22,21;,
 3;21,22,23;,
 3;24,25,26;,
 3;27,24,26;,
 3;28,27,26;,
 3;29,28,26;,
 3;30,29,26;,
 3;31,30,26;,
 3;32,31,26;,
 3;33,32,26;,
 3;34,33,26;,
 3;35,34,26;,
 3;25,35,26;,
 3;36,37,38;,
 3;36,38,39;,
 3;36,39,40;,
 3;36,40,41;,
 3;36,41,42;,
 3;36,42,43;,
 3;36,43,44;,
 3;36,44,45;,
 3;36,45,46;,
 3;36,46,47;,
 3;36,47,37;,
 3;48,49,50;,
 3;50,49,51;,
 3;49,52,51;,
 3;51,52,53;,
 3;52,54,53;,
 3;53,54,55;,
 3;54,56,55;,
 3;55,56,57;,
 3;56,58,57;,
 3;57,58,59;,
 3;58,60,59;,
 3;59,60,61;,
 3;60,62,61;,
 3;61,62,63;,
 3;62,64,63;,
 3;63,64,65;,
 3;64,66,65;,
 3;65,66,67;,
 3;66,68,67;,
 3;67,68,69;,
 3;68,48,69;,
 3;69,48,50;,
 3;63,65,44;,
 3;44,65,45;,
 3;65,67,45;,
 3;45,67,46;,
 3;67,69,46;,
 3;46,69,47;,
 3;69,50,47;,
 3;47,50,37;,
 3;50,51,37;,
 3;37,51,38;,
 3;51,53,38;,
 3;38,53,39;,
 3;53,55,39;,
 3;39,55,40;,
 3;55,57,40;,
 3;40,57,41;,
 3;57,59,41;,
 3;41,59,42;,
 3;59,61,42;,
 3;42,61,43;,
 3;61,63,43;,
 3;43,63,44;;
 
 MeshMaterialList {
  12;
  88;
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10;;
  Material {
   0.429600;0.429600;0.429600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game317\\Desktop\\ドラゴン・ノスケ\\T\\4.png";
   }
  }
  Material {
   0.429600;0.429600;0.429600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game317\\Desktop\\ドラゴン・ノスケ\\T\\3.png";
   }
  }
  Material {
   0.385600;0.385600;0.385600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game317\\Desktop\\ドラゴン・ノスケ\\T\\3.png";
   }
  }
  Material {
   0.385600;0.385600;0.385600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game317\\Desktop\\ドラゴン・ノスケ\\T\\3.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.197600;0.197600;0.197600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game317\\Desktop\\ドラゴン・ノスケ\\T\\3.png";
   }
  }
  Material {
   0.385600;0.385600;0.385600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game317\\Desktop\\ドラゴン・ノスケ\\T\\3.png";
   }
  }
  Material {
   0.385600;0.104800;0.065600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.385600;0.385600;0.385600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game317\\Desktop\\ドラゴン・ノスケ\\T\\2.png";
   }
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  50;
  0.889916;0.000000;-0.456124;,
  0.502046;0.000000;-0.864841;,
  -0.045219;0.000000;-0.998977;,
  -0.578129;0.000000;-0.815946;,
  -0.927485;0.000000;-0.373859;,
  -0.982373;-0.000000;0.186929;,
  -0.725364;-0.000000;0.688366;,
  -0.238059;-0.000000;0.971251;,
  0.324834;-0.000000;0.945771;,
  0.784589;-0.000000;0.620016;,
  0.995244;-0.000000;0.097411;,
  0.784588;0.000000;-0.620017;,
  0.324832;0.000000;-0.945772;,
  -0.238057;0.000000;-0.971251;,
  -0.725363;0.000000;-0.688367;,
  -0.982373;0.000000;-0.186930;,
  -0.927486;-0.000000;0.373859;,
  -0.578131;-0.000000;0.815944;,
  -0.045220;-0.000000;0.998977;,
  0.502048;-0.000000;0.864840;,
  0.889917;-0.000000;0.456123;,
  0.995244;0.000000;-0.097409;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;-0.000001;,
  -0.000004;1.000000;-0.000002;,
  -0.000001;1.000000;-0.000005;,
  0.000003;1.000000;-0.000003;,
  0.238060;0.000000;-0.971250;,
  -0.324833;0.000000;-0.945771;,
  0.045221;0.000000;-0.998977;,
  -0.502048;0.000000;-0.864840;,
  -0.784590;0.000000;-0.620015;,
  -0.889917;0.000000;-0.456122;,
  -0.995244;0.000000;-0.097410;,
  -0.995244;0.000000;0.097410;,
  -0.889917;-0.000000;0.456122;,
  -0.784590;-0.000000;0.620015;,
  -0.502048;-0.000000;0.864840;,
  -0.324833;-0.000000;0.945771;,
  0.045219;-0.000000;0.998977;,
  0.238056;-0.000000;0.971251;,
  0.578130;-0.000000;0.815945;,
  0.725366;-0.000000;0.688364;,
  0.927487;-0.000000;0.373854;,
  0.982374;-0.000000;0.186927;,
  0.982373;0.000000;-0.186929;,
  0.927486;0.000000;-0.373857;,
  0.725365;0.000000;-0.688364;,
  0.578132;0.000000;-0.815943;;
  88;
  3;0,1,11;,
  3;11,1,12;,
  3;1,2,12;,
  3;12,2,13;,
  3;2,3,13;,
  3;13,3,14;,
  3;3,4,14;,
  3;14,4,15;,
  3;4,5,15;,
  3;15,5,16;,
  3;5,6,16;,
  3;16,6,17;,
  3;6,7,17;,
  3;17,7,18;,
  3;7,8,18;,
  3;18,8,19;,
  3;8,9,19;,
  3;19,9,20;,
  3;9,10,20;,
  3;20,10,21;,
  3;10,0,21;,
  3;21,0,11;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;24,23,25;,
  3;24,25,26;,
  3;24,26,27;,
  3;24,27,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;28,29,30;,
  3;30,29,31;,
  3;29,32,31;,
  3;31,32,33;,
  3;32,34,33;,
  3;33,34,35;,
  3;34,36,35;,
  3;35,36,37;,
  3;36,38,37;,
  3;37,38,39;,
  3;38,40,39;,
  3;39,40,41;,
  3;40,42,41;,
  3;41,42,43;,
  3;42,44,43;,
  3;43,44,45;,
  3;44,46,45;,
  3;45,46,47;,
  3;46,48,47;,
  3;47,48,49;,
  3;48,28,49;,
  3;49,28,30;;
 }
 MeshTextureCoords {
  70;
  0.375000;0.312500;,
  0.397730;0.312500;,
  0.375000;0.688440;,
  0.397730;0.688440;,
  0.420460;0.312500;,
  0.420460;0.688440;,
  0.443180;0.312500;,
  0.443180;0.688440;,
  0.465910;0.312500;,
  0.465910;0.688440;,
  0.488640;0.312500;,
  0.488640;0.688440;,
  0.511360;0.312500;,
  0.511360;0.688440;,
  0.534090;0.312500;,
  0.534090;0.688440;,
  0.556820;0.312500;,
  0.556820;0.688440;,
  0.579550;0.312500;,
  0.579550;0.688440;,
  0.602270;0.312500;,
  0.602270;0.688440;,
  0.625000;0.312500;,
  0.625000;0.688440;,
  0.564910;0.014120;,
  0.631450;0.071770;,
  0.500000;0.150000;,
  0.477760;0.001590;,
  0.397680;0.038160;,
  0.350080;0.112230;,
  0.350080;0.200270;,
  0.397680;0.274340;,
  0.477760;0.310910;,
  0.564910;0.298380;,
  0.631450;0.240720;,
  0.656250;0.156250;,
  0.500000;0.837500;,
  0.597910;0.905080;,
  0.548350;0.948020;,
  0.483440;0.957360;,
  0.423780;0.930110;,
  0.388330;0.874950;,
  0.388330;0.809370;,
  0.423780;0.754200;,
  0.483440;0.726950;,
  0.548350;0.736290;,
  0.597910;0.779230;,
  0.616390;0.842150;,
  0.631450;0.928220;,
  0.564910;0.985880;,
  0.597910;0.905080;,
  0.548350;0.948020;,
  0.477760;0.998410;,
  0.483440;0.957360;,
  0.397680;0.961840;,
  0.423780;0.930110;,
  0.350080;0.887770;,
  0.388330;0.874950;,
  0.350080;0.799730;,
  0.388330;0.809370;,
  0.397680;0.725660;,
  0.423780;0.754200;,
  0.477760;0.689090;,
  0.483440;0.726950;,
  0.564910;0.701620;,
  0.548350;0.736290;,
  0.631450;0.759280;,
  0.597910;0.779230;,
  0.656250;0.843750;,
  0.616390;0.842150;;
 }
}
