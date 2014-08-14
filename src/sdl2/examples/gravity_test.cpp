/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <iostream>

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include <cstdio>

using namespace std;

bool drawBody(
  SDL_Renderer* renderer,
  b2Body* body, 
  int r, int g, int b 
  ) 
{ 
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  int ox = 320;
  int oy = 400;
  float sc = 40.0;
  //http://box2d.org/forum/viewtopic.php?f=3&t=1933
  for( b2Fixture *fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext() )
  {
    if( fixture->GetType() == b2Shape::e_polygon )
    {
      b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();

      const int count = poly->GetVertexCount();

      for( int i = 0; i < count; i++ )
      {
        int ind0 = (i + 1) % count ;
        b2Vec2 p0 = body->GetWorldPoint(  poly->GetVertex( ind0 ) );
        b2Vec2 p1 = body->GetWorldPoint(  poly->GetVertex(i) );

#if 0
        std::cout << i << " " << ind0 << " " 
          << p0.x << " " << p0.y << " "
          << p1.x << " " << p1.y << " "
          << std::endl;
#endif

        SDL_RenderDrawLine(renderer, 
            sc * p0.x + ox, -sc * p0.y + oy ,
            sc * p1.x + ox, -sc * p1.y + oy
            );

      }
      //verts now contains world co-ords of all the verts
    }
  }
}


// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
// There are no graphics for this example. Box2D is meant to be used
// with your rendering engine in your game engine.
int main(int argc, char** argv)
{

  /// SDL stuff
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window;

  window = SDL_CreateWindow( 
      "An SDL2 window",         //    const char* title
      0, //SDL_WINDOWPOS_UNDEFINED,  //    int x: initial x position
      0, //SDL_WINDOWPOS_UNDEFINED,  //    int y: initial y position
      640,                      //    int w: width, in pixels
      480,                      //    int h: height, in pixels
      SDL_WINDOW_SHOWN          //    Uint32 flags: window options, see docs
      );

  // Check that the window was successfully made
  if(window==NULL){   
    // In the event that the window could not be made...
    std::cout << "Could not create window: " << SDL_GetError() << '\n';
    SDL_Quit(); 
    return 1;
  }

  SDL_Renderer* renderer;

  renderer = SDL_CreateRenderer(window, -1, 0);

  // Select the color for drawing. It is set to red here.
  SDL_SetRenderDrawColor(renderer, 100, 100, 250, 255);

  // Clear the entire screen to our selected color.
  SDL_RenderClear(renderer);

  // Up until now everything was drawn behind the scenes.
  // This will show the new, red contents of the window.
  SDL_RenderPresent(renderer);
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  /////////////////////////////////////////////////////


  // BOX2D stuff
	
  B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f, bodyDef.position, 1.0);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

  int event_pending = 0;
  SDL_Event event;

	// This is our little game loop.
  bool do_loop = true;
	while (do_loop)
  {
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

    SDL_SetRenderDrawColor(renderer, 100, 100, 250, 255);
    SDL_RenderClear(renderer);


    drawBody(renderer, groundBody, 255,255,155);
    drawBody(renderer, body, 255,255,255);

    SDL_RenderPresent(renderer);
    SDL_Delay(20);  // Wait for 3000 milliseconds, for example
    
    {
      event_pending = SDL_PollEvent(&event);

      if (event_pending == 0) continue;
    
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym = SDLK_q) do_loop = false;
        if (event.key.keysym.sym = SDLK_ESCAPE) do_loop = false;
        
      }
    }
  }

    
	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

   
    
  // The window is open: enter program loop (see SDL_PollEvent)
  
  // Close and destroy the window
  SDL_DestroyWindow(window); 
  
  // Clean up SDL2 and exit the program
  SDL_Quit(); 


	return 0;
}

