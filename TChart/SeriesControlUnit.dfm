object SeriesControlForm: TSeriesControlForm
  Left = 360
  Top = 248
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077'/'#1091#1076#1072#1083#1077#1085#1080#1077'/'#1085#1072#1089#1090#1088#1086#1081#1082#1072' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1081
  ClientHeight = 369
  ClientWidth = 529
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poDesktopCenter
  OnHide = FormHide
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 298
    Height = 369
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 298
      Height = 175
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      object Panel5: TPanel
        Left = 240
        Top = 0
        Width = 58
        Height = 175
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 0
        object Button1: TButton
          Left = 10
          Top = 13
          Width = 41
          Height = 20
          Hint = #1053#1072#1095#1072#1090#1100' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1077' '#1079#1072' '#1074#1089#1077#1084' '#1090#1086#1095#1082#1072#1084#1080
          Caption = '>>>'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          OnClick = Button1Click
        end
        object Button2: TButton
          Left = 10
          Top = 65
          Width = 41
          Height = 20
          Hint = #1053#1072#1095#1072#1090#1100' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1077
          Caption = '>'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          OnClick = Button2Click
        end
        object Button3: TButton
          Left = 10
          Top = 91
          Width = 41
          Height = 20
          Hint = #1055#1088#1077#1088#1074#1072#1090#1100' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1077
          Caption = '<'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          OnClick = Button3Click
        end
        object Button4: TButton
          Left = 10
          Top = 141
          Width = 41
          Height = 20
          Hint = #1055#1088#1077#1088#1074#1072#1090#1100' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1077' '#1079#1072' '#1074#1089#1077#1084#1080' '#1090#1086#1095#1082#1072#1084#1080
          Caption = '<<<'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
          OnClick = Button4Click
        end
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 6
        Width = 239
        Height = 170
        Caption = ' '#1044#1086#1089#1090#1091#1087#1085#1099#1077' '#1090#1086#1095#1082#1080' '
        TabOrder = 1
        object StringGrid1: TStringGrid
          Left = 2
          Top = 15
          Width = 235
          Height = 153
          Align = alClient
          ColCount = 2
          FixedCols = 0
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
          TabOrder = 0
          OnDblClick = StringGrid1DblClick
        end
      end
    end
    object Panel1: TPanel
      Left = 0
      Top = 175
      Width = 298
      Height = 194
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 1
      object GroupBox2: TGroupBox
        Left = 7
        Top = 7
        Width = 228
        Height = 150
        Caption = ' '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1082#1085#1072' '
        TabOrder = 0
        DesignSize = (
          228
          150)
        object CheckBox2: TCheckBox
          Left = 7
          Top = 104
          Width = 104
          Height = 14
          Caption = #1055#1086#1076#1087#1080#1089#1100' '#1086#1089#1080' Y:'
          TabOrder = 0
          OnClick = CheckBox2Click
        end
        object Edit2: TEdit
          Left = 23
          Top = 118
          Width = 192
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          Color = clActiveBorder
          Enabled = False
          TabOrder = 1
          OnChange = Edit2Change
        end
        object CheckBox4: TCheckBox
          Left = 7
          Top = 85
          Width = 104
          Height = 13
          Caption = #1064#1082#1072#1083#1072' '#1087#1086' '#1086#1089#1080' Y'
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = CheckBox4Click
        end
        object Edit1: TEdit
          Left = 22
          Top = 55
          Width = 193
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          Color = clActiveBorder
          Enabled = False
          TabOrder = 3
          OnChange = Edit1Change
        end
        object CheckBox1: TCheckBox
          Left = 7
          Top = 39
          Width = 104
          Height = 14
          Caption = #1055#1086#1076#1087#1080#1089#1100' '#1086#1089#1080' X:'
          TabOrder = 4
          OnClick = CheckBox1Click
        end
        object CheckBox3: TCheckBox
          Left = 7
          Top = 20
          Width = 104
          Height = 13
          Caption = #1064#1082#1072#1083#1072' '#1087#1086' '#1086#1089#1080' X'
          Checked = True
          State = cbChecked
          TabOrder = 5
          OnClick = CheckBox3Click
        end
      end
    end
  end
  object Panel3: TPanel
    Left = 298
    Top = 0
    Width = 231
    Height = 369
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 1
    object Panel6: TPanel
      Left = 0
      Top = 175
      Width = 231
      Height = 194
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        231
        194)
      object Label1: TLabel
        Left = 7
        Top = 7
        Width = 3
        Height = 13
      end
      object BitBtn1: TBitBtn
        Left = 45
        Top = 163
        Width = 87
        Height = 26
        Anchors = [akRight, akBottom]
        Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
        DoubleBuffered = True
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
        ModalResult = 1
        NumGlyphs = 2
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = BitBtn1Click
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 7
        Width = 228
        Height = 150
        Caption = ' '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1103' '
        TabOrder = 1
        DesignSize = (
          228
          150)
        object Label2: TLabel
          Left = 20
          Top = 20
          Width = 50
          Height = 13
          Caption = #1055#1086#1076#1087#1080#1089#1100': '
        end
        object Label3: TLabel
          Left = 39
          Top = 72
          Width = 28
          Height = 13
          Alignment = taRightJustify
          Caption = #1062#1074#1077#1090':'
        end
        object Label4: TLabel
          Left = 10
          Top = 46
          Width = 57
          Height = 13
          Alignment = taRightJustify
          Caption = #1057#1084#1077#1097#1077#1085#1080#1077':'
        end
        object Edit3: TEdit
          Left = 72
          Top = 16
          Width = 150
          Height = 21
          Hint = #1044#1074#1086#1081#1085#1086#1081' '#1097#1077#1083#1095#1086#1082', '#1095#1090#1086#1073#1099' '#1080#1079#1084#1077#1085#1080#1090#1100' '#1087#1086#1076#1087#1080#1089#1100
          Anchors = [akLeft, akTop, akRight]
          Color = clActiveBorder
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 0
          OnDblClick = Edit3DblClick
        end
        object Edit4: TEdit
          Left = 72
          Top = 43
          Width = 150
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 1
          Text = '0'
          OnExit = Edit4Exit
          OnKeyDown = Edit4KeyDown
        end
        object OutterCPanel: TPanel
          Left = 72
          Top = 68
          Width = 150
          Height = 20
          Hint = #1044#1074#1086#1081#1085#1086#1081' '#1097#1077#1083#1095#1086#1082', '#1095#1090#1086#1073#1099' '#1080#1079#1084#1077#1085#1080#1090#1100' '#1094#1074#1077#1090
          Anchors = [akLeft, akTop, akRight]
          BevelInner = bvLowered
          BevelOuter = bvSpace
          Color = clWhite
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          OnDblClick = OutterCPanelDblClick
          DesignSize = (
            150
            20)
          object InnerCPanel: TPanel
            Left = 7
            Top = 7
            Width = 137
            Height = 7
            Hint = #1044#1074#1086#1081#1085#1086#1081' '#1097#1077#1083#1095#1086#1082', '#1095#1090#1086#1073#1099' '#1080#1079#1084#1077#1085#1080#1090#1100' '#1094#1074#1077#1090
            Anchors = [akLeft, akTop, akRight]
            BevelOuter = bvNone
            Color = clBlack
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnDblClick = InnerCPanelDblClick
          end
        end
        object CheckBox5: TCheckBox
          Left = 7
          Top = 98
          Width = 215
          Height = 13
          Anchors = [akLeft, akTop, akRight]
          Caption = #1054#1090#1082#1083#1102#1095#1080#1090#1100' '#1074#1089#1077' '#1087#1086#1076#1087#1080#1089#1080
          Checked = True
          State = cbChecked
          TabOrder = 3
          OnClick = CheckBox5Click
        end
      end
      object BitBtn2: TBitBtn
        Left = 143
        Top = 163
        Width = 85
        Height = 26
        Caption = #1054#1090#1084#1077#1085#1072
        DoubleBuffered = True
        Kind = bkCancel
        ParentDoubleBuffered = False
        TabOrder = 2
        OnClick = BitBtn2Click
      end
    end
    object GroupBox4: TGroupBox
      Left = 0
      Top = 6
      Width = 228
      Height = 170
      Caption = ' '#1053#1072#1073#1083#1102#1076#1072#1077#1084#1099#1077' '#1090#1086#1095#1082#1080' '
      TabOrder = 1
      object StringGrid2: TStringGrid
        Left = 2
        Top = 15
        Width = 224
        Height = 153
        Align = alClient
        ColCount = 2
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
        TabOrder = 0
        OnClick = StringGrid2Click
        OnDblClick = StringGrid2DblClick
      end
    end
  end
  object ColorDialog1: TColorDialog
    Options = [cdFullOpen]
    Left = 310
    Top = 233
  end
end
