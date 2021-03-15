object ListInputForm: TListInputForm
  Left = 327
  Top = 267
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsDialog
  Caption = 'ListInputForm'
  ClientHeight = 294
  ClientWidth = 488
  Color = clBtnFace
  Constraints.MinHeight = 150
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnHide = FormHide
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object List: TStringGrid
    Left = 0
    Top = 0
    Width = 488
    Height = 216
    Align = alClient
    ColCount = 1
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
    TabOrder = 0
    OnDblClick = ListDblClick
  end
  object Panel1: TPanel
    Left = 0
    Top = 216
    Width = 488
    Height = 78
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object BitBtn1: TBitBtn
      Left = 152
      Top = 40
      Width = 91
      Height = 33
      Caption = 'OK'
      Default = True
      TabOrder = 0
      OnClick = BitBtn1Click
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object BitBtn2: TBitBtn
      Left = 248
      Top = 40
      Width = 89
      Height = 33
      Caption = '������'
      TabOrder = 1
      Kind = bkCancel
    end
    object Edit: TEdit
      Left = 3
      Top = 8
      Width = 481
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 2
      OnChange = EditChange
      OnKeyDown = EditKeyDown
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 488
    Height = 97
    BevelOuter = bvNone
    TabOrder = 2
    Visible = False
    object Button1: TButton
      Left = 208
      Top = 71
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = '��'
      TabOrder = 0
      OnClick = Button1Click
    end
  end
end
