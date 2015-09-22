#pragma once

void controlModelOnce(Model* model)
{
	if (GetAsyncKeyState('P')) model->add(5);
	else if (GetAsyncKeyState('O')) model->del(5);

	if (GetAsyncKeyState('W')) model->accelerate(Vector(0, -0.05, 0));
	if (GetAsyncKeyState('S')) model->accelerate(Vector(0, 0.05, 0));
	if (GetAsyncKeyState('A')) model->accelerate(Vector(-0.05, 0, 0));
	if (GetAsyncKeyState('D')) model->accelerate(Vector(0.05, 0, 0));

	if (GetAsyncKeyState('L')) model->slowdown(0.01);
}

void calculateModelOnce(Model* model)
{
	model->move();
	model->wallBounce();
	model->ballBounce();
}

void renderModelOnce(Model* model, Renderer* renderer, const COLORREF* colorMap, const size_t colorMapSize)
{
	if (!model->getBallArrayPointer()->empty())
	{
		for (std::forward_list<Ball>::iterator i = model->getBallArrayPointer()->begin();
		i != model->getBallArrayPointer()->end(); i++)
		{
			renderer->render(*i, colorMap, colorMapSize, 0, 10);
		}
	}
}

void controlEverything(Model* model, Renderer* renderer)
{
    COLORREF colormap[4] =
    {
        RGB(128,   0,   0),
        RGB(255, 250,   0),
        RGB(255, 255, 255),
        RGB(200, 100, 250)
    };

	for (size_t calcsAfterRendering = 0; !GetAsyncKeyState(VK_ESCAPE); calcsAfterRendering++)
    {
		controlModelOnce(model);

		calculateModelOnce(model);

		if (calcsAfterRendering >= 5)
		{
			calcsAfterRendering = 0;

			renderer->startRendering();
			renderer->clear();

			renderModelOnce(model, renderer, colormap, 4);
			
			renderer->finishRendering();
		}
    }
}
