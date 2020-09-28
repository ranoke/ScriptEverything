import wx
import wx.xrc
import functional
import threading

###########################################################################
# Class MainWindow
###########################################################################

class MainWindow ( wx.Frame ):

	target_proccess_name = ""
	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"ScriptEverything Launcher", pos = wx.DefaultPosition, size = wx.Size( 300,300 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )

		self.SetSizeHints( wx.Size( 300,300 ), wx.Size( 300,300 ) )

		self.m_menubar1 = wx.MenuBar( 0 )
		self.m_file = wx.Menu()
		self.m_download = wx.MenuItem( self.m_file, wx.ID_ANY, u"Download", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_file.Append( self.m_download )

		self.m_settings = wx.MenuItem( self.m_file, wx.ID_ANY, u"Settings", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_file.Append( self.m_settings )

		self.m_menubar1.Append( self.m_file, u"File" )

		self.m_about = wx.Menu()
		self.m_info = wx.MenuItem( self.m_about, wx.ID_ANY, u"Info", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_about.Append( self.m_info )

		self.m_help = wx.MenuItem( self.m_about, wx.ID_ANY, u"Get help", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_about.Append( self.m_help )

		self.m_menubar1.Append( self.m_about, u"About" )

		self.SetMenuBar( self.m_menubar1 )

		fgSizer2 = wx.FlexGridSizer( 0, 2, 0, 0 )
		fgSizer2.SetFlexibleDirection( wx.BOTH )
		fgSizer2.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )

		self.m_process_name = wx.TextCtrl( self, wx.ID_ANY, u"process_name", wx.DefaultPosition, wx.Size( 180,-1 ), 0 )
		fgSizer2.Add( self.m_process_name, 0, wx.ALL, 5 )

		self.m_load = wx.Button( self, wx.ID_ANY, u"Load", wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer2.Add( self.m_load, 0, wx.ALL, 5 )


		self.SetSizer( fgSizer2 )
		self.Layout()

		self.Centre( wx.BOTH )

		# Connect Events
		self.Bind( wx.EVT_MENU, self.action_download, id = self.m_download.GetId() )
		self.m_process_name.Bind( wx.EVT_TEXT, self.proc_name_change )
		self.m_load.Bind( wx.EVT_BUTTON, self.load )	

	def __del__( self ):
		pass


	# Virtual event handlers, overide them in your derived class
	def action_download( self, event ):
		threading.Thread(target=functional.download).start()

	def proc_name_change( self, event ):
		self.target_proccess_name = event.GetString()

	def load( self, event ):
		print(self.target_proccess_name) 
		threading.Thread(target = functional.inject, args=[self.target_proccess_name]).start()

def main():
    app = wx.App(useBestVisual=True)

    frame = MainWindow(None)
    frame.Show()

    app.MainLoop()


if __name__ == "__main__":
    main()
