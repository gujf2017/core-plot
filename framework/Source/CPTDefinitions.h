#import <Availability.h>
#import <TargetConditionals.h>

/// @file

/**
 *  @def CPT_SDK_SUPPORTS_WEAK
 *  @hideinitializer
 *  @brief Defined as @num{1} if the compiler and active SDK support weak references, @num{0} otherwise.
 **/

/**
 *  @def cpt_weak
 *  @hideinitializer
 *  @brief A custom definition for automatic reference counting (ARC) weak references that falls back to
 *  <code>__unsafe_unretained</code> values on older platforms.
 **/

/**
 *  @def cpt_weak_property
 *  @hideinitializer
 *  @brief A custom definition for automatic reference counting (ARC) weak properties that falls back to
 *  <code>assign</code> on older platforms.
 **/

// This is based on Ryan Petrich's ZWRCompatibility: https://github.com/rpetrich/ZWRCompatibility

#if TARGET_OS_IPHONE && defined(__IPHONE_5_0) && (__IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_5_0) && __clang__ && (__clang_major__ >= 3)
#define CPT_SDK_SUPPORTS_WEAK 1
#elif TARGET_OS_MAC && defined(__MAC_10_7) && (MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_7) && __clang__ && (__clang_major__ >= 3)
#define CPT_SDK_SUPPORTS_WEAK 1
#else
#define CPT_SDK_SUPPORTS_WEAK 0
#endif

#if CPT_SDK_SUPPORTS_WEAK
#define cpt_weak          __weak
#define cpt_weak_property weak
#else
#if __clang__ && (__clang_major__ >= 3)
#define cpt_weak __unsafe_unretained
#else
#define cpt_weak
#endif
#define cpt_weak_property assign
#endif

// Deprecated method attribute

/**
 *  @def cpt_deprecated
 *  @hideinitializer
 *  @brief Marks a method declaration as deprecated.
 **/

#define cpt_deprecated __attribute__( (deprecated) )

// Nullability

/**
 *  @def cpt_nullable
 *  @hideinitializer
 *  @brief Marks a pointer declaration as nullable.
 **/

/**
 *  @def cpt_nonnull
 *  @hideinitializer
 *  @brief Marks a pointer declaration as non-null.
 **/

#if __clang__ && ( ( (__clang_major__ == 6) && (__clang_minor__ >= 1 ) ) || (__clang_major__ > 6 ) )
// nullable symbols are already defined
#else
#define nullable
#define nonnull
#define __nullable
#define __nonnull
#endif

// Deprecated methods

/**
 *  @def cpt_deprecated
 *  @hideinitializer
 *  @brief Marks a method declaration as deprecated.
 **/

#define cpt_deprecated __attribute__( (deprecated) )

// Type safety defines

/**
 *  @def CPTFloat
 *  @hideinitializer
 *  @param x The number to cast.
 *  @brief Casts a number to @ref CGFloat.
 **/
#define CPTFloat(x) ( (CGFloat)(x) )

/**
 *  @def CPTPointMake
 *  @hideinitializer
 *  @param x The x-coordinate of the point.
 *  @param y The y-coordinate of the point.
 *  @brief A replacement for @ref CGPointMake(), casting each parameter to @ref CGFloat.
 **/
#define CPTPointMake(x, y) CGPointMake( (CGFloat)(x), (CGFloat)(y) )

/**
 *  @def CPTSizeMake
 *  @hideinitializer
 *  @param w The width of the size.
 *  @param h The height of the size.
 *  @brief A replacement for @ref CGSizeMake(), casting each parameter to @ref CGFloat.
 **/
#define CPTSizeMake(w, h) CGSizeMake( (CGFloat)(w), (CGFloat)(h) )

/**
 *  @def CPTRectMake
 *  @hideinitializer
 *  @param x The x-coordinate of the rectangle.
 *  @param y The y-coordinate of the rectangle.
 *  @param w The width of the rectangle.
 *  @param h The height of the rectangle.
 *  @brief A replacement for @ref CGRectMake(), casting each parameter to @ref CGFloat.
 **/
#define CPTRectMake(x, y, w, h) CGRectMake( (CGFloat)(x), (CGFloat)(y), (CGFloat)(w), (CGFloat)(h) )

/**
 *  @def CPTRectInset
 *  @hideinitializer
 *  @param rect The rectangle to offset.
 *  @param dx The x-offset.
 *  @param dy The y-offset.
 *  @brief A replacement for @ref CGRectInset(), casting each offset parameter to @ref CGFloat.
 **/
#define CPTRectInset(rect, dx, dy) CGRectInset( rect, (CGFloat)(dx), (CGFloat)(dy) )

/**
 *  @brief Enumeration of numeric types
 **/
typedef NS_ENUM (NSInteger, CPTNumericType) {
    CPTNumericTypeInteger, ///< Integer
    CPTNumericTypeFloat,   ///< Float
    CPTNumericTypeDouble   ///< Double
};

/**
 *  @brief Enumeration of error bar types
 **/
typedef NS_ENUM (NSInteger, CPTErrorBarType) {
    CPTErrorBarTypeCustom,        ///< Custom error bars
    CPTErrorBarTypeConstantRatio, ///< Constant ratio error bars
    CPTErrorBarTypeConstantValue  ///< Constant value error bars
};

/**
 *  @brief Enumeration of axis scale types
 **/
typedef NS_ENUM (NSInteger, CPTScaleType) {
    CPTScaleTypeLinear,   ///< Linear axis scale
    CPTScaleTypeLog,      ///< Logarithmic axis scale
    CPTScaleTypeAngular,  ///< Angular axis scale (not implemented)
    CPTScaleTypeDateTime, ///< Date/time axis scale (not implemented)
    CPTScaleTypeCategory  ///< Category axis scale
};

/**
 *  @brief Enumeration of axis coordinates
 **/
typedef NS_ENUM (NSInteger, CPTCoordinate) {
    CPTCoordinateX    = 0,           ///< X axis
    CPTCoordinateY    = 1,           ///< Y axis
    CPTCoordinateZ    = 2,           ///< Z axis
    CPTCoordinateNone = NSIntegerMax ///< Invalid coordinate value
};

/**
 *  @brief RGBA color for gradients
 **/
typedef struct _CPTRGBAColor {
    CGFloat red;   ///< The red component (0 ≤ @par{red} ≤ 1).
    CGFloat green; ///< The green component (0 ≤ @par{green} ≤ 1).
    CGFloat blue;  ///< The blue component (0 ≤ @par{blue} ≤ 1).
    CGFloat alpha; ///< The alpha component (0 ≤ @par{alpha} ≤ 1).
}
CPTRGBAColor;

/**
 *  @brief Enumeration of label positioning offset directions
 **/
typedef NS_ENUM (NSInteger, CPTSign) {
    CPTSignNone     = 0,  ///< No offset
    CPTSignPositive = +1, ///< Positive offset
    CPTSignNegative = -1  ///< Negative offset
};

/**
 *  @brief Locations around the edge of a rectangle.
 **/
typedef NS_ENUM (NSInteger, CPTRectAnchor) {
    CPTRectAnchorBottomLeft,  ///< The bottom left corner
    CPTRectAnchorBottom,      ///< The bottom center
    CPTRectAnchorBottomRight, ///< The bottom right corner
    CPTRectAnchorLeft,        ///< The left middle
    CPTRectAnchorRight,       ///< The right middle
    CPTRectAnchorTopLeft,     ///< The top left corner
    CPTRectAnchorTop,         ///< The top center
    CPTRectAnchorTopRight,    ///< The top right
    CPTRectAnchorCenter       ///< The center of the rect
};

/**
 *  @brief Label and constraint alignment constants.
 **/
typedef NS_ENUM (NSInteger, CPTAlignment) {
    CPTAlignmentLeft,   ///< Align horizontally to the left side.
    CPTAlignmentCenter, ///< Align horizontally to the center.
    CPTAlignmentRight,  ///< Align horizontally to the right side.
    CPTAlignmentTop,    ///< Align vertically to the top.
    CPTAlignmentMiddle, ///< Align vertically to the middle.
    CPTAlignmentBottom  ///< Align vertically to the bottom.
};

/**
 *  @brief Edge inset distances for stretchable images.
 **/
typedef struct _CPTEdgeInsets {
    CGFloat top;    ///< The top inset.
    CGFloat left;   ///< The left inset.
    CGFloat bottom; ///< The bottom inset.
    CGFloat right;  ///< The right inset.
}
CPTEdgeInsets;

extern const CPTEdgeInsets CPTEdgeInsetsZero; ///< Defines a set of stretchable image edge insets where all of the values are zero (@num{0}).

typedef void (^CPTQuickLookImageBlock)(__nonnull CGContextRef context, CGFloat scale, CGRect bounds); ///< Render a Quick Look image into the given context.
