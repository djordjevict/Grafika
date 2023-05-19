
// MFCApplication1View.cpp : implementation of the CMFCApplication1View class
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCApplication1View construction/destruction

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: add construction code here

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}




//---------------------------------------------------------------------------------------------------------------------------
//TRNSFORMACIJE

void CMFCApplication1View::Shear(CDC* pDC, float sX, float sY, bool strana)
{
	XFORM transform{};
	transform.eM11 = transform.eM22 = 1;
	transform.eM12 = sY;
	transform.eM21 = sX;

	pDC->ModifyWorldTransform(&transform, strana ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMFCApplication1View::Scale(CDC* pDC, float sX, float sY, bool strana)
{
	XFORM transform{};
	transform.eM12 = transform.eM21 = 0;
	transform.eM11 = sX;
	transform.eM22 = sY;

	pDC->ModifyWorldTransform(&transform, strana ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMFCApplication1View::Translate(CDC* pDC, float dX, float dY, bool strana)
{
	XFORM transform = { 1, 0, 0, 1, dX, dY };

	pDC->ModifyWorldTransform(&transform, strana ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMFCApplication1View::Rotate(CDC* pDC, float angle, bool strana)
{
	XFORM transform{};
	transform.eM11 = transform.eM22 = cos(angle);
	transform.eM21 = -sin(angle);
	transform.eM12 = sin(angle);

	pDC->ModifyWorldTransform(&transform, strana ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}


//---------------------------------------------------------------------------------------------------------------------------
//MAJ 2021

void CMFCApplication1View::DrawConeBottom1(CDC* pDC, float cX, float cY, float a, float b, float h, int n)
{
	double dAlpha = 2.0 * 3.14 / n,
		angle = 0;

	double dColor = 2.0 * 255.0 / n,
		color = 0;

	CPoint* elipse = new CPoint[n];
	CBrush* oldBrush = pDC->GetCurrentBrush();

	for (int i = 0; i < n; i++)
	{
		elipse[i] = { (int)(cX + a * cos(angle)), (int)(cY + h + b * sin(angle)) };
		angle -= dAlpha;

		if (angle >= -3.14 && i > 0)
		{
			CPoint niz[3] = { elipse[i - 1], { (int)(cX), (int)(cY) }, elipse[i] };
			CBrush brush(RGB((int)(color), (int)(color), (int)(color)));
			pDC->SelectObject(&brush);
			pDC->Polygon(niz, 3);
			pDC->SelectObject(oldBrush)->DeleteObject();
			color += dColor;
		}
	}

	CBrush brush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);
	pDC->Polygon(elipse, n);
	pDC->SelectObject(oldBrush)->DeleteObject();
	delete[] elipse;
}
void CMFCApplication1View::DrawConeTop1(CDC* pDC, float cX, float cY, float a, float b, float h, int n)
{
	double dAlpha = 2.0 * 3.14 / n,
		angle = 0;

	double dColor = 2.0 * 255.0 / n,
		color = 0;

	CPoint* elipse = new CPoint[n];
	CBrush* oldBrush = pDC->GetCurrentBrush();

	for (int i = 0; i <= n >> 1; i++)
	{
		elipse[i] = { (int)(cX + a * cos(angle)), (int)(cY + h + b * sin(angle))};
		angle += dAlpha;

		if (angle >= -3.14 && i > 0)
		{
			CPoint niz[3] = { elipse[i - 1], { (int)(cX), (int)(cY) }, elipse[i] };
			CBrush brush(RGB((int)(color), (int)(color), (int)(color)));
			pDC->SelectObject(&brush);
			pDC->Polygon(niz, 3);
			pDC->SelectObject(oldBrush)->DeleteObject();
			color += dColor;
		}
	}
}
void CMFCApplication1View::DrawCylinder1(CDC* pDC, float cX, float cY, float a, float b, float h, int n)
{
	double dAlpha = 2.0 * 3.14 / n,
		angle = 0;

	double dColor = 2.0 * 255.0 / n,
		color = 0;

	CPoint* elipse = new CPoint[n];
	CBrush* oldBrush = pDC->GetCurrentBrush();

	for (int i = 0; i < n; i++)
	{
		elipse[i] = { (int)(cX + a * cos(angle)), (int)(cY + h + b * sin(angle)) };
		angle -= dAlpha;

		if (angle >= -3.14 && i > 0)
		{
			CPoint niz[4] = { elipse[i - 1], { elipse[i - 1].x, (int)(elipse[i - 1].y - h) }, { elipse[i].x, (int)(elipse[i].y - h) } , elipse[i] };
			CBrush brush(RGB((int)(color), (int)(color), (int)(color)));
			pDC->SelectObject(&brush);
			pDC->Polygon(niz, 4);
			pDC->SelectObject(oldBrush)->DeleteObject();
			color += dColor;
		}
	}

	CBrush brush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);
	pDC->Polygon(elipse, n);
	pDC->SelectObject(oldBrush)->DeleteObject();
	delete[] elipse;
}
void CMFCApplication1View::DrawFigure1(CDC* pDC, float cX, float cY, float a, float b, float h, int n, float r)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	Translate(pDC, cX, cY, false);
	Rotate(pDC, -3.14 / 4.0, false);

	Translate(pDC, 0, r, false);
	DrawCylinder1(pDC, 0, 0, a, b, h, n);

	Translate(pDC, 0, -r, false); 

	Rotate(pDC, -3.14 / 2.0, false);
	
	Translate(pDC, 0, r, false);
	DrawConeBottom1(pDC, 0, 0, a, b, h, n);

	Translate(pDC, 0, -r, false);

	Rotate(pDC, -3.14 / 2.0, false);
	
	Translate(pDC, 0, r, false);
	DrawConeTop1(pDC, 0, 0, a, b, h, n);

	Translate(pDC, 0, -r, false); 

	Rotate(pDC, -3.14 / 2.0, false);
	Translate(pDC, 0, r, false);
	DrawConeTop1(pDC, 0, 0, a, b, h, n);

	pDC->SetWorldTransform(&state);
}


//---------------------------------------------------------------------------------------------------------------------------
//JUN 2022

void CMFCApplication1View::DrawScene(CDC* pDC)
{
	CRect window;
	GetClientRect(&window); 

	XFORM state{};
	pDC->GetWorldTransform(&state);

	float a = 20, b = 50, h = 100, ugao = 3.14/8;
	int nSeg = 8, n = 3;
	Translate(pDC, window.Width() / 2.0, window.Height() / 2.0, false);  

	DrawFigure(pDC, 0, 0, a, b, h, nSeg, n, ugao, 1);

	pDC->SetWorldTransform(&state);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, 1000, 1000);
	HGDIOBJ old = memDC->SelectObject(&bm);

	memDC->StretchBlt(0, 0, 1000, 1000, pDC, window.left, window.top, window.Width(), window.Height(), SRCCOPY);

	DImage img(*memDC->GetCurrentBitmap());
	img.Save(CString("figure.jpg"));

	delete(memDC->SelectObject(old));
	delete(memDC);
}
void CMFCApplication1View::DrawFigure(CDC* pDC, float Cx, float Cy, float a, float b, float h, float nSeg, float n, float alpha, int currLevel)
{
	if (currLevel <= n)
	{

		if ((currLevel % 2) == 0)
		{
			DrawCylinder(pDC, Cx, Cy, a, b, h, nSeg);
			Translate(pDC, -a, -h, false);
			Rotate(pDC, -alpha, false);
			Scale(pDC, 0.5, 0.5, false);
			DrawFigure(pDC, Cx, Cy, a, b, h, nSeg, n, alpha, currLevel + 1);
			Scale(pDC, 2, 2, false);
			Rotate(pDC, alpha, false);
			Translate(pDC, a, h, false);
			Translate(pDC, a, -h, false);
			Rotate(pDC, alpha, false);
			Scale(pDC, 0.5, 0.5, false);
			DrawFigure(pDC, Cx, Cy, a, b, h, nSeg, n, alpha, currLevel + 1);
			Scale(pDC, 2, 2, false);
			Rotate(pDC, -alpha, false);
			Translate(pDC, -a, h, false);
		}
		else
		{
			DrawCone(pDC, Cx, Cy, a, b, h, nSeg);
			Translate(pDC, -a, -h, false);
			Rotate(pDC, -alpha, false);
			Scale(pDC, 0.5, 0.5, false);
			DrawFigure(pDC, Cx, Cy, a, b, h, nSeg, n, alpha, currLevel + 1);
			Scale(pDC, 2, 2, false);
			Rotate(pDC, alpha, false);
			Translate(pDC, a, h, false);
			Translate(pDC, a, -h, false);
			Rotate(pDC, alpha, false);
			Scale(pDC, 0.5, 0.5, false);
			DrawFigure(pDC, Cx, Cy, a, b, h, nSeg, n, alpha, currLevel + 1);
			Scale(pDC, 2, 2, false);
			Rotate(pDC, -alpha, false);
			Translate(pDC, -a, h, false);
		}
	}
}
void CMFCApplication1View::DrawCone(CDC* pDC, float cx, float cy, float a, float b, float h, float nSeg)
{
	float alpha = 2 * 3.14 / nSeg;
	float alphaP = 0;

	float color = 2 * 255 / nSeg;
	float colorP = 0;

	CBrush* old = pDC->GetCurrentBrush();
	CPoint* elipsa = new CPoint[nSeg+1];		// ide +1 da bi se ponovo odradila prva tacka od koje je poceto, 
												//kako bi i ona nacrtala pravougaonik i povezala se sa prethodnom tackom
												//jer prvi put kad se ona crta, ne zna za svog prethodnika
	for (int i = 0; i <= nSeg; i++)
	{
		elipsa[i] = { (int)(cx + a*cos(alphaP)), (int)(cy - h + b * sin(alphaP))};
		if (alphaP < -3.15 && i > 0)
		{
			CPoint niz[3] = { elipsa[i-1], {(int)(cx),(int)(cy)}, elipsa[i]};
			pDC->SelectObject(new CBrush(RGB(colorP, colorP, colorP)));
			pDC->Polygon(niz, 3);
			pDC->SelectObject(old)->DeleteObject();
		}
		colorP += color;
		alphaP -= alpha;
	}

	pDC->SelectObject(new CBrush(RGB(255, 255, 255)));
	pDC->Polygon(elipsa, nSeg);
	pDC->SelectObject(old)->DeleteObject();
	delete[] elipsa;
}
void CMFCApplication1View::DrawCylinder(CDC* pDC, float cx, float cy, float a, float b, float h, float nSeg)
{
	float alpha = 2 * 3.14 / nSeg;
	float alphaP = 0;

	float color = 2 * 255 / nSeg;
	float colorP = 0;

	CBrush* old = pDC->GetCurrentBrush();
	CPoint* elipsa = new CPoint[nSeg+1];

	for (int i = 0; i <= nSeg; i++)
	{
		elipsa[i] = { (int)(cx + a * cos(alphaP)), (int)(cy - h + b * sin(alphaP))};
		if (alphaP < -3.15 && i > 0)
		{
			CPoint niz[4] = { elipsa[i - 1], {(int)(elipsa[i-1].x), (int)(elipsa[i-1].y + h)}, {elipsa[i].x, (int)(elipsa[i].y + h)}, elipsa[i]};
			pDC->SelectObject(new CBrush(RGB(colorP, colorP, colorP)));
			pDC->Polygon(niz, 4);
			pDC->SelectObject(old);
		}
		colorP += color;
		alphaP -= alpha;
	}

	pDC->SelectObject(new CBrush(RGB(255, 255, 255)));
	pDC->Polygon(elipsa, nSeg);
	pDC->SelectObject(old);
	delete[] elipsa;
}


//---------------------------------------------------------------------------------------------------------------------------
//JUN 2 2022

void CMFCApplication1View::DrawWheel(CDC* pDC, double r1, double r2, double w)
{
	XFORM transform{};
	pDC->GetWorldTransform(&transform);

	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(255 / 3, 255 / 3, 255 / 3)));

	pDC->Ellipse(-r1, -r1, r1, r1);
	CBrush* siva = pDC->SelectObject(oldBrush);
	pDC->Ellipse(-r2, -r2, r2, r2);
	oldBrush = pDC->SelectObject(siva);

	double ugao = 2 * 3.14 / 6;
	for (int i = 0; i < 3; i++)
	{
		pDC->Rectangle(-w / 2, -r2, w / 2, r2);
		Rotate(pDC, -ugao, false);
	}

	pDC->SelectObject(oldBrush)->DeleteObject();
	pDC->SetWorldTransform(&transform);
}
void CMFCApplication1View::DrawWP(CDC* pDC, double r1, double r2, double w, double L, double alpha, double d)
{
	CRect window;
	GetClientRect(&window);

	XFORM state{};
	pDC->GetWorldTransform(&state);

	Translate(pDC, window.Width()/2, window.Height()/2, false);

	double hipotenuza = L / sin(3.14 / 2 - alpha);
	double a = hipotenuza * cos(3.14 / 2 - alpha);
	CPoint niz[3] = { {(int)( - L / 2),0},{(int)(-L / 2), (int)(-a)},{(int)(L / 2),0}};
	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(255 / 3, 255 / 3, 255 / 3)));
	pDC->Polygon(niz, 3);
	pDC->SelectObject(oldBrush);

	Translate(pDC, -L / 2, -a - r1, false);
	Rotate(pDC, alpha, false);
	//DrawWheel(pDC, r1, r2, w);
	Translate(pDC, d, 0, false);
	Rotate(pDC, d / r1, false);
	DrawWheel(pDC, r1, r2, w);

	pDC->SetWorldTransform(&state);
}
void CMFCApplication1View::CMipMaps(CDC* pDC, CString str)
{
	DImage* img = new DImage();
	img->Load(str);
	img->Flip();

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	
	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, img->Width(), img->Height());
	CBitmap* old = memDC->SelectObject(bm);

	float w = img->Width(),
		h = img->Height(),
		w0 = 0,
		h0 = 0;

	while (w > 0 && h > 0)
	{
		img->Draw(memDC, CRect(0, 0, img->Width(), img->Height()), CRect(w0, img->Height() - h, w0 + w, img->Height()));
		w0 = w;
		h0 = h;
		w /= 2;
		h /= 2;
	}

	delete(memDC->SelectObject(old));
	delete(memDC);
}


//---------------------------------------------------------------------------------------------------------------------------
//JANUAR 2022

void CMFCApplication1View::DrawMagnifiedBitmap(CDC* pDC, int mag, CString name)
{
	CRect window;
	GetClientRect(window);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, window.Width(), window.Height());
	CBitmap* old = memDC->SelectObject(bm);

	memDC->SetMapMode(MM_ANISOTROPIC);

	memDC->SetWindowExt(window.Width() / mag, window.Height() / mag);
	memDC->SetViewportExt(window.Width(), window.Height());
	memDC->SetViewportOrg(0, 0);
	memDC->Rectangle(window);
	DrawPuzzle(pDC, 40, 3.14 / 3, window.Width() / 2, window.Height() / 2);

	DImage img(*memDC->GetCurrentBitmap());
	img.Save(name);

	delete(memDC->SelectObject(old));
	delete(memDC);
}
void CMFCApplication1View::DrawPuzzle(CDC* pDC, int size, float angle, int x, int y)
{
	Translate(pDC, x, y, false);

	XFORM state{};
	pDC->GetWorldTransform(&state);		
	//1. nacin koji je zakomentarisan
	Rotate(pDC, -angle, false);
	DrawPart1(pDC, size);
	Translate(pDC, 2*size, 0, false);
	DrawPart2(pDC, size);
	Translate(pDC, 2*size, 0, false);
	DrawPart1(pDC, size);

	//pDC->SetWorldTransform(&state);

	Translate(pDC, -4 * size, 0, false);
	Rotate(pDC, 3.14/2, false);
	Translate(pDC, -2*size, 0, false);
	DrawPart3(pDC, size);
	Translate(pDC, -2*size, 0, false);
	DrawPart4(pDC, size);
	

/*	//2. nacin
	Rotate(pDC, angle, false);
	DrawPart1(pDC, size);
	Translate(pDC, 0, -2 * size, false);
	Rotate(pDC, 3.14/2, false);
	DrawPart2(pDC, size);
	Rotate(pDC, -3.14 / 2, false);
	Translate(pDC, 0, -2 * size, false);
	DrawPart1(pDC, size);
	Translate(pDC, 0, 4 * size, false);
	Rotate(pDC, 3.14/2, false);
	Translate(pDC, 0, 2 * size, false);
	DrawPart3(pDC, size);
	Translate(pDC, 0, 2 * size, false);
	Rotate(pDC, 3.14/2, false);
	DrawPart4(pDC, size);*/

	pDC->SetWorldTransform(&state);

	/*
	Difoltno za ARC je suprotno od kazaljke na satu		******************************************************************************************************
	Difoltno za SVE OSTALO je kao kazaljka na satu	***************************************************************************************************
	*/

}
void CMFCApplication1View::DrawPart1(CDC* pDC, int size)
{
	CBrush* old = pDC->SelectObject(new CBrush(RGB(255, 255, 255)));
	CPoint niz[4] = { {size,-size},{-size,-size},{-size,size},{size,size} };
	//CPoint niz[4] = { {-size,-size},{-size,size},{size,size},{size,-size} };
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->BeginPath();
	{
		pDC->Polyline(niz, 4);
		pDC->Arc(0, -size, 2 * size, size, niz[0].x, niz[0].y, niz[3].x, niz[3].y);
		//pDC->Arc(-size, -2 * size, size, 0, -size, -size, size, -size);
	}
	pDC->EndPath();

	pDC->StrokeAndFillPath();
	pDC->SelectObject(old);
}
void CMFCApplication1View::DrawPart2(CDC* pDC, int size)
{
	CBrush* old = pDC->SelectObject(new CBrush(RGB(255/3, 255/3, 255/3)));
	CPoint niz[4] = { {-size,-size},{size,-size},{size,size},{-size,size} };
	//CPoint niz[4] = { {size,-size},{-size,-size},{-size,size},{size,size} };
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->BeginPath();
	{
		pDC->Polyline(niz, 4);
		pDC->Arc(-2*size, -size, 0, size, niz[0].x, niz[0].y, niz[3].x, niz[3].y);
		//pDC->Arc(0,-size, 2*size, size,size, size,size, -size);
	}
	pDC->EndPath();

	pDC->StrokeAndFillPath();
	pDC->SelectObject(old);
}
void CMFCApplication1View::DrawPart3(CDC* pDC, int size)
{
	CBrush* old = pDC->SelectObject(new CBrush(RGB(255 / 3, 255 / 3, 255 / 3)));
	CPoint niz[5] = { {-size,-size},{size,-size},{size,size},{-size,size},{0,0} };
	//CPoint niz[5] = { {-size,size},{-size,-size},{size,-size},{size,size},{0,0} };

	pDC->BeginPath();
	{
		pDC->Polygon(niz, 5);
	}
	pDC->EndPath();

	pDC->StrokeAndFillPath();
	pDC->SelectObject(old);
}
void CMFCApplication1View::DrawPart4(CDC* pDC, int size)
{
	CBrush* old = pDC->SelectObject(new CBrush(RGB(0, 0, 0)));
	CPoint niz[5] = { {-size,-size},{size,-size},{2*size,0},{size,size},{-size,size}};
	//CPoint niz[5] = { {-2*size,0},{-size,-size},{size,-size},{size,size},{-size,size} };

	pDC->BeginPath();
	{
		pDC->Polygon(niz, 5);
	}
	pDC->EndPath();

	pDC->StrokeAndFillPath();
	pDC->SelectObject(old);
}


//---------------------------------------------------------------------------------------------------------------------------
//APRIL 2022

void CMFCApplication1View::DrawCybin(CDC* pDC, int w, int d, COLORREF color, CString string)
{
	int red = GetRValue(color);
	int blue = GetBValue(color);
	int green = GetGValue(color);
	CBrush* old = pDC->SelectObject(new CBrush(RGB(GetRValue(color), GetGValue(color), GetBValue(color))));

	CPoint niz[4] = { {-w,(int)(w + 0.45 * w)}, {-w,(int)(3 * w + 0.45 * w)}, {w,(int)(3 * w + 0.45 * w)}, {w,(int)(w + 0.45 * w)} };
	pDC->BeginPath();
	{
		pDC->Polyline(niz, 4);
		pDC->Arc(-w, 0.45*w, w, 2 * w+0.45*w, w, w+0.45*w, -w, w+0.45*w);
	}
	pDC->EndPath();

	pDC->StrokeAndFillPath();
	delete(pDC->SelectObject(old));

	pDC->MoveTo(0, 0);
	pDC->LineTo(0, 0.45*w);  //treba svuda gde je 0,45 da pise 0.25 ali je mnogo malo ne vidi se zato sam promenila 

	XFORM state{};
	pDC->GetWorldTransform(&state);
	Translate(pDC, 0, 2 * w + 0.45 * w, false);
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	CSize size = pDC->GetTextExtent(string);
	pDC->TextOut(-size.cx/2, -size.cy/2, string);
	pDC->SetWorldTransform(&state);
}
void CMFCApplication1View::DrawWheel1(CDC* pDC, int r, int d, int n, COLORREF color)
{
	CPen* old = pDC->SelectObject(new CPen(PS_SOLID, 3 * d, RGB(0, 0, 0)));
	pDC->Ellipse(-r, -r, r, r);
	pDC->Ellipse(-0.8 * r, -0.8 * r, 0.8 * r, 0.8 * r);
	delete(pDC->SelectObject(old));

	CPen* old1 = pDC->SelectObject(new CPen(PS_SOLID, d, RGB(0, 0, 0)));
	CBrush* old2 = pDC->SelectObject(new CBrush(RGB(0,0,0)));
	pDC->Ellipse(-0.1 * r, -0.1 * r, 0.1 * r, 0.1 * r);
	delete(pDC->SelectObject(old2));

	XFORM state{};
	pDC->GetWorldTransform(&state);
	float ugao = 2 * 3.14 / n;
	for (int i = 0; i < n/2; i++)
	{
		pDC->MoveTo(-r, 0);
		pDC->LineTo(r, 0);
		Rotate(pDC, ugao, false);
	}
	pDC->SetWorldTransform(&state);
}
void CMFCApplication1View::DrawObservationWheel(CDC* pDC, int r, int d, int n, COLORREF color, CString arStrp[], CPoint point, float alpha, int k)
{
	Translate(pDC, point.x, point.y, false);
	CPoint niz[3] = { {0,0}, {(int)( - 0.8 * r / 2),(int)(1.6 * r)}, {(int)(0.8 * r / 2),(int)(1.6 * r)}};
	CPen* old = pDC->SelectObject(new CPen(PS_SOLID, 3*d, RGB(0, 0, 0)));
	pDC->Polygon(niz, 3);
	XFORM state{};
	pDC->GetWorldTransform(&state);
	Rotate(pDC, -alpha, false);
	DrawWheel1(pDC, r, d, n, color);
	int brKabina = n / k;
	int ugaoKabina = 2 * 3.14 / brKabina;
	for (int i = 0; i < brKabina; i++)
	{
		Translate(pDC, r, 0, false);
		Rotate(pDC, alpha+i*ugaoKabina, false);
		DrawCybin(pDC, 0.2 * r, d, color, arStrp[i]);
		Rotate(pDC, -alpha-i*ugaoKabina, false);
		Translate(pDC, -r, 0, false);
		Rotate(pDC, -ugaoKabina, false);
	}
	pDC->SetWorldTransform(&state);
}
void CMFCApplication1View::SaveDC(CDC* pDC, CRect rect1, CRect rect2, CString name)
{
	CRect window;
	GetClientRect(&window);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, rect2.Width(), rect2.Height());
	CBitmap* old = memDC->SelectObject(bm);

	memDC->StretchBlt(rect2.left, rect2.top, rect2.Width(), rect2.Height(), pDC, rect1.left, rect1.top, rect1.Width(), rect1.Height(), SRCCOPY);

	DImage img(*bm);
	img.Save(name);

	delete(memDC->SelectObject(old));
	delete(memDC);
}


//---------------------------------------------------------------------------------------------------------------------------
//DECEMBAR 2022 - samo neka proba nisam znala da uradim

void CMFCApplication1View::DrawCanTop(CDC* pDC, DImage* img, float cx, float cy, float a, float b, int n, int h)
{
	CRect win;
	GetClientRect(win);
	
	CRgn* rgn1 = new CRgn(), * rgn2 = new CRgn(), * rgn3 = new CRgn();
	rgn1->CreateRectRgn(0, 0, win.Width(), win.Height());
	rgn2->CreateEllipticRgn(cx-b, cy-a, cx+b, cy+a);
	rgn3->CreateRectRgn(0, 0, 0, 0);
	rgn3->CombineRgn(rgn1, rgn2, RGN_AND);
	pDC->SelectClipRgn(rgn3);
	
	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, win.Width(), win.Height()));
}
void CMFCApplication1View::DrawCanWrapper(CDC* pDC, DImage* img, float cx, float cy, float a, float b, int n, int h)
{
	//ne znam kako skaliranjem da nacrtam omotac
}
void CMFCApplication1View::DrawCan(CDC* pDC, float cx, float cy, float a, float b, int n, int h)
{
	DImage* img = new DImage();
	img->Load(CString("nzm.jpg"));
	img->Flip();

	DImage* img2 = new DImage();
	img2->Load(CString("nzm.jpg"));
	img2->Flip();

	DrawCanTop(pDC, img, cx, cy, a, b, 2 * n, h);
	DrawCanWrapper(pDC, img2, cx, cy, a, b, n, h);
}


//---------------------------------------------------------------------------------------------------------------------------
//OKTOBAR 2022

void CMFCApplication1View::DrawCycle(CDC* pDC, int r, int n, int d)
{
	CPen* newP = new CPen(PS_SOLID, d, RGB(0, 0, 0));
	CPen* oldP = pDC->SelectObject(newP);

	pDC->Ellipse(-r, -r, r, r);

	CBrush* newB = new CBrush(RGB(0, 0, 0));
	CBrush* oldB = pDC->SelectObject(newB);

	pDC->SelectObject(oldP);
	pDC->Ellipse(-2 * d, -2 * d, 2 * d, 2 * d);

	pDC->SelectObject(oldB);
	CPoint* niz = new CPoint[2];
	niz[0] = { 0,0 };
	float alfa = 0,
		dAlfa = 2 * 3.14 / n;
	for (int i = 1; i <= n; i++)
	{
		niz[1] = {(int)(r*cos(alfa)),(int)(r*sin(alfa))};
		alfa -= dAlfa;
		pDC->Polyline(niz, 2);
	}
}
void CMFCApplication1View::DrawBicycle(CDC* pDC, int r, int n, int d, float alpha, float beta)
{
	//veliki tocak
	DrawCycle(pDC, r, n, d);

	CPen* newP = new CPen(PS_SOLID, d, RGB(0, 0, 0));
	CPen* oldP = pDC->SelectObject(newP);

	//veliki luk
	pDC->Arc(-1.2 * r, -1.2 * r, 1.2 * r, 1.2 * r, 1.2 * r, 0, 0, -1.2 * r);

	//prednji nosac i upravljac bicikle
	pDC->LineTo(0, -1.4 * r);
	pDC->LineTo(0.2*r, -1.4*r);  
	pDC->MoveTo(0, 0);

	//manji luk
	pDC->Arc(1.2*r, -3 * r / 4, 1.2 * r + 2 * 3*r / 4, 3*r / 4, 1.2 * r, 0, 1.2 * r + 3 *r / 4, 3*r / 4);

	//linija na prelazu dva luka
	Translate(pDC, 1.2 * r, 0, false);
	pDC->LineTo(0.1 * r, 0);
	pDC->MoveTo(0, 0);

	//mali tocak
	Translate(pDC, 3 * r / 4, 3 * r / 4, false);
	oldP = pDC->SelectObject(oldP);
	DrawCycle(pDC, r / 4, n, d/2);
	oldP = pDC->SelectObject(oldP);
	Translate(pDC, -1.2 * r - 3 * r / 4, -3 * r / 4, false);

	//sediste
	Rotate(pDC, -beta, false);
	Translate(pDC, 1.2 * r, 0, false);
	CPoint* niz = new CPoint[2];
	niz[0] = { 0,0 };
	niz[1] = { (int)(0.2 * r),0 };
	pDC->Polyline(niz, 2);
	Translate(pDC, 0.2 * r, 0, false);
	Rotate(pDC, beta, false);
	niz[0] = { (int)(-0.15 * r),0 };
	niz[1] = { (int)(0.15 * r),0 };
	pDC->Polyline(niz, 2);
	Rotate(pDC, -beta, false);
	Translate(pDC, -1.4 * r, 0, false);
	Rotate(pDC, beta, false);

	//pedala
	Rotate(pDC, alpha, false);
	niz[0] = { (int)(- 0.2 * r),0};
	niz[1] = { (int)(0.2 * r),0 };
	pDC->Polyline(niz, 2);
	Translate(pDC, -0.2 * r, 0, false);
	Rotate(pDC, -alpha, false);
	niz[0] = { (int)(-0.1 * r),0 };
	niz[1] = { (int)(0.1 * r),0 };
	pDC->Polyline(niz, 2);
	Rotate(pDC, alpha, false);
	Translate(pDC, 0.4 * r, 0, false);
	Rotate(pDC, -alpha, false);
	niz[0] = { (int)(-0.1 * r),0 };
	niz[1] = { (int)(0.1 * r),0 };
	pDC->Polyline(niz, 2);
	Rotate(pDC, alpha, false);
	Translate(pDC, -0.2 * r, 0, false);
	Rotate(pDC, -alpha, false);
}
void CMFCApplication1View::DrawText1(CDC* pDC, int size, CString text, COLORREF clr)
{
	CSize vel = pDC->GetTextExtent(text);
	pDC->SetTextColor(clr);
	CFont font;
	font.CreateFontW(8, 8, 900, 900, size, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
	pDC->SelectObject(font);
	pDC->TextOutW(0, 0, text);
}
void CMFCApplication1View::SaveDC1(CDC* pDC, CRect rect1, CRect rect2, CString name)
{
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, rect2.Width(), rect2.Height());
	CBitmap* old = memDC->SelectObject(bm);

	memDC->StretchBlt(rect2.left, rect2.top, rect2.Width(), rect2.Height(), pDC, rect1.left, rect1.top, 
																		rect1.Width(), rect1.Height(), SRCCOPY);
	DImage* img = new DImage(*bm);
	img->Save(name);

	delete(memDC->SelectObject(old));
	delete(memDC);
}




void CMFCApplication1View::OnDraw(CDC* pDC)
{
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);

	/*	//MAJ 2021
	CRect window;
	GetClientRect(&window);
	DrawFigure1(pDC, window.Width() / 2.0, window.Height() / 2.0, 50, 25, 100, 20, 50);*/

	//DrawScene(pDC);		//JUN 2022

	//DrawWP(pDC, 40, 30, 8, 240, 3.14 / 6, 80);		//JUN 2 2022

	DrawMagnifiedBitmap(pDC, 2, CString("januar2022"));		//JANUAR 2022 

	/*		//APRIL 2022
	CString arStr[] = { L"1.",L"2.",L"3.",L"4.",L"5.",L"6." };
	CRect window;
	GetClientRect(&window);
	DrawObservationWheel(pDC, 100, 1.5, 12, RGB(252, 42, 42), arStr, CPoint(window.Width() / 2.0, window.Height() / 2.0), 3.14 / 6, 2);
	SaveDC(pDC, CRect(0, 0, window.Width() / 2, window.Height()), window, CString("april2022"));*/

	/*		//DECEMBAR 2022
	CRect window;
	GetClientRect(&window);
	DrawCan(pDC, window.Width() / 2, window.Height() / 2, 20, 25, 6, 80);*/

	/*	//pisanje teksta
	CRect w;
	GetClientRect(&w);
	CSize size = pDC->GetTextExtent(CString("Teodora"));
	CFont font;
	font.CreateFontW(size.cx, size.cy, -900, -900, 2, 0, 0, 0, 0, 0, 0, 0, 0, CString("Times New Roman"));
	pDC->SelectObject(font);
	pDC->TextOutW(w.Width() / 2, w.Height() / 2, CString("Teodora"));  */

	//OKTOBAR 2022
	/*CRect win;
	GetClientRect(win);
	Translate(pDC, win.Width() / 2, win.Height() / 2, false);
	DrawBicycle(pDC, 100, 12, 4, 3.14 / 6, 60 * 3.14 / 180);
	Translate(pDC, 1.2 * 100 + 100, 100, false);
	DrawText1(pDC, 2, CString("Teodora Djordjevic"), COLORREF(RGB(252, 0, 255)));
	//SaveDC1(pDC, CRect(0, 0, win.Width() / 2, win.Height() / 2), CRect(0, 0, win.Width(), win.Height()),CString("abc.jpg"));*/

	pDC->SetGraphicsMode(oldGM);
}


// CMFCApplication1View printing

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCApplication1View diagnostics

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View message handlers
