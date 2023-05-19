
// MFCApplication1View.h : interface of the CMFCApplication1View class
//

#pragma once
#include "DImage.h"

class CMFCApplication1View : public CView
{
protected: // create from serialization only
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// Attributes
public:
	CMFCApplication1Doc* GetDocument() const;

// Operations
public:
	void Scale(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Shear(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);

	void DrawConeBottom1(CDC* pDC, float cX, float cY, float a, float b, float h, int n);
	void DrawConeTop1(CDC* pDC, float cX, float cY, float a, float b, float h, int n);
	void DrawCylinder1(CDC* pDC, float cX, float cY, float a, float b, float h, int n);
	void DrawFigure1(CDC* pDC, float cX, float cY, float a, float b, float h, int n, float r);
	
	void DrawScene(CDC* pDC);
	void DrawFigure(CDC* pDC, float Cx, float Cy, float a, float b, float h, float nSeg, float n, float alpha, int currLevel);
	void DrawCone(CDC* pDC, float Cx, float Cy, float a, float b, float h, float nSeg);
	void DrawCylinder(CDC* pDC, float Cx, float Cy, float a, float b, float h, float nSeg);

	void DrawWheel(CDC* pDC, double r1, double r2, double w);
	void DrawWP(CDC* pDC, double r1, double r2, double w, double L, double alpha, double d);
	void CMipMaps(CDC* pDC, CString str);

	void DrawMagnifiedBitmap(CDC* pDC, int mag, CString name);
	void DrawPuzzle(CDC* pDC, int size, float angle, int x, int y);
	void DrawPart1(CDC* pDC, int size);
	void DrawPart2(CDC* pDC, int size);
	void DrawPart3(CDC* pDC, int size);
	void DrawPart4(CDC* pDC, int size);

	void DrawCybin(CDC* pDC, int w, int d, COLORREF color, CString string);
	void DrawWheel1(CDC* pDC, int r, int d, int n, COLORREF color);
	void DrawObservationWheel(CDC* pDC, int r, int d, int n, COLORREF color, CString arStrp[], CPoint point, float alpha, int k);
	void SaveDC(CDC* pDC, CRect rect1, CRect rect2, CString name);

	void DrawCanTop(CDC* pDC, DImage* img, float cx, float cy, float a, float b, int n, int h);
	void DrawCanWrapper(CDC* pDC, DImage* img, float cx, float cy, float a, float b, int n, int h);
	void DrawCan(CDC* pDC, float cx, float cy, float a, float b, int n, int h);

	void DrawCycle(CDC* pDC, int r, int n, int d);
	void DrawBicycle(CDC* pDC, int r, int n, int d, float alpha, float beta);
	void DrawText1(CDC* pDC, int size, CString text, COLORREF clr);
	void SaveDC1(CDC* pDC, CRect rect1, CRect rect2, CString name);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCApplication1View.cpp
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

