object WatchFrame: TWatchFrame
  Left = 0
  Top = 0
  Width = 656
  Height = 469
  TabOrder = 0
  TabStop = True
  object Chart1: TChart
    Left = 0
    Top = 0
    Width = 656
    Height = 469
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    MarginBottom = 0
    MarginTop = 0
    Title.Text.Strings = (
      ' ')
    DepthAxis.Automatic = False
    DepthAxis.AutomaticMaximum = False
    DepthAxis.AutomaticMinimum = False
    DepthAxis.Maximum = -0.700000000000000600
    DepthAxis.Minimum = -1.700000000000001000
    LeftAxis.Title.Angle = 0
    Legend.Inverted = True
    Legend.LegendStyle = lsSeries
    Legend.Visible = False
    View3D = False
    Align = alClient
    Color = clWhite
    TabOrder = 0
  end
  object SavePictureDialog: TSavePictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp|Enhanced Metafiles (*.emf)|*.emf'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1075#1088#1072#1092#1080#1082' '#1082#1072#1082
    Left = 16
    Top = 16
  end
end
