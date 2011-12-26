#ifndef JOTHELLOPROTOCOL_H
#define JOTHELLOPROTOCOL_H

/**
  quint8 protocol,
  EOP_Ready:
    c-s:
    s-c: quint8 at
  EOP_PutChess:
    c-s: quint8 (x%8)*8+(y%8)
    s-c: quint8 (at%2)*64 + (x%8)*8 + (y%8)
  EOP_GameOver:
    s-c: quint8 winner
    0 : at0
    1 : at1
    2 : draw
  EOP_Escape:
    s-c: quint8 at
  EOP_Reset:
    s-c: quint8 type
    chess 1;
    ready 2;
    按位与。
  */
enum EOthelloProtocol{
    EOP_Ready,
    EOP_PutChess,
    EOP_GameOver,
    EOP_Escape,
    EOP_Reset,
};

enum EResetType{
    ERT_Othello = 1,
    ERT_Ready = 2,
};

#endif // JOTHELLOPROTOCOL_H
