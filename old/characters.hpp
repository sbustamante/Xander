/****************************************************************************************
			      CLASSES
****************************************************************************************/
//OBJECT CLASS ==========================================================================
class Object
{
    //Atributes
    public:
	//Object Name
	char* object_name;
	//Coordinates
	SDL_Rect coor;
	//Size
	SDL_Rect size;
	//Picture Path
	char* picture_path;
	//SDL Surface
	SDL_Surface *surface;
	
    //Methods
    public:
	//Set Object Name 
	void SetName( char* name ){ 
	    object_name = name; }
	//Set Coordinates
	void SetCoordinates( float , float );
	//Set Object Size
	void SetSize( float, float );
	//Set Surface and Load BMP Picture
	void SetSurface( char* );
	//Draw Object
	void Draw( SDL_Surface* );
	
};

//Set Coordinates........................................................................
void Object::SetCoordinates( float x, float y )
{
    coor.x = x;
    coor.y = y;
}

//Set Object Size........................................................................
void Object::SetSize( float h, float w )
{
    size.x = h;
    size.y = w;
}

//Set Surface and Load BMP Picture.......................................................
void Object::SetSurface( char* path )
{
    //Path of Picture
    picture_path = path;
    //Loading Picture
    surface = SDL_LoadBMP( picture_path );
    //Applying Transparency
    SDL_SetColorKey(surface, 
		    SDL_SRCCOLORKEY, 
		    SDL_MapRGB(surface->format, 0, 255, 0));
}

//Draw Object............................................................................
void Object::Draw( SDL_Surface* HiddenScreen )
{
    SDL_BlitSurface(surface, NULL, HiddenScreen, &coor);
}




//ENVIRONMENT ===========================================================================
class Environment
{
    //Atributes
    public:
	//Environment Name
	char* environment_name;
	//Scenary Path
	char* scn_path;
	//Scenary Matrix
	int scn[50][50];
	//SDL Surface
	SDL_Surface *surface;
	//SDL Hidden Surface
	SDL_Surface *hidden_surface;
	//Rect of Environment
	SDL_Rect rect_surf;
	//Objects of the Ground
	Object ground[50][50];
	
    //Methods
    public:
	//Set Object Name 
	void SetName( char* name ){ 
	    environment_name = name; }
	//Load Scenario
	void LoadScenario( char* );
	//Initalizing Scenario
 	void Initalize( );
	//Surfaces of the Scenario
 	void SetSurfaces( );
	//Draw Scenario
 	void Draw( );
	//Update Scenario
	void Update( );
	
};

//Load Scenario..........................................................................
void Environment::LoadScenario( char* path )
{
    FILE *file_scn;
    int i = 0;
    
    scn_path = path;
    
    //Loading Scn file
    file_scn = fopen( scn_path, "r" );
    
    while( getc( file_scn ) != EOF )
    {
	fscanf( file_scn, "\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
		&scn[0][i], &scn[1][i], &scn[2][i], &scn[3][i],
		&scn[4][i], &scn[5][i], &scn[6][i], &scn[7][i],
		&scn[8][i], &scn[9][i], &scn[10][i], &scn[11][i],
		&scn[12][i], &scn[13][i], &scn[14][i], &scn[15][i]);
	i++;
    }
    fclose( file_scn );
}

//Initalizing Scenario...................................................................
void Environment::Initalize( )
{
    hidden_surface = SDL_CreateRGBSurface( SDL_SWSURFACE, SCREEN_SIZE_X, SCREEN_SIZE_Y, 
					   32, 0, 0, 0, 0);
					   
    //Intiliaze SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {	
	printf("Couldn't be initalized SDL: %s\n", SDL_GetError());
	exit(1);
    }
    
    //Initalize Windows
    surface = SDL_SetVideoMode( SCREEN_SIZE_X, SCREEN_SIZE_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    if( surface == NULL )
    {
	printf( "Error al entrar a modo grafico: %s\n", SDL_GetError() );
	SDL_Quit();
    }
    
    //Caption of windows
    SDL_WM_SetCaption( environment_name, environment_name );
}

//Trace Scenario.........................................................................
void Environment::SetSurfaces( )
{
    string path_tmp;
    int i, j;
    
    //Recursive Loading of Scenario According SCN matrix
    for(i=0;i<SCN_X;i++)
	for(j=0;j<SCN_Y;j++)
	{ 
	    ground[i][j].SetSize( SCN_H, SCN_W );
	    ground[i][j].coor.x = ground[i][j].size.x*i;
	    ground[i][j].coor.y = ground[i][j].size.y*j;
 	    path_tmp = DATA_FOLDER+SCN_FOLDER +"land"+toString(scn[i][j])+".bmp";
	    
	    ground[i][j].SetSurface( (char*)path_tmp.c_str() );
	    SDL_BlitSurface( ground[i][j].surface, NULL, hidden_surface, &ground[i][j].coor );
	}
}

//Draw Scenario..........................................................................
void Environment::Draw( )
{
    int i, j;
    
    //Recursive Loading of Scenario According SCN matrix
    for(i=0;i<SCN_X;i++)
	for(j=0;j<SCN_Y;j++)
	    SDL_BlitSurface( ground[i][j].surface, NULL, hidden_surface, &ground[i][j].coor );
	
}

//Update Scenario........................................................................
void Environment::Update( )
{ 
    rect_surf.x = 0;
    rect_surf.y = 0;
    SDL_BlitSurface( hidden_surface, NULL, surface, &rect_surf );
    SDL_Flip( surface );
}