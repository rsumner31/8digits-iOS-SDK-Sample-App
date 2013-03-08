//
//  EDNetwork.h
//  EightDigits
//
//  Created by Seyithan Teymur on 23/07/12.
//  Copyright (c) 2012 Epigraf. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
	Name of the notification that's posted when an EDVisit object changes authorisation status
 */
static NSString *EDVisitDidChangeAuthorisationStatusNotification = @"EDVisitDidChangeAuthorisationStatusNotification";
	
/**
	8digits visit
 */
@interface EDVisit : NSObject <NSCoding>


/**
	8digits URL prefix
	@default string value with EDURLPrefix key inside EightDigits.plist.
 */
@property (nonatomic, strong)							NSString	*urlPrefix;

/**
	8digits Tracking code
	@default string value with EDTrackingCode key inside EightDigits.plist.
 */
@property (nonatomic, strong)							NSString	*trackingCode;

/**
	Session authorization token
 */
@property (nonatomic, strong, readonly)					NSString	*authToken;

/**
	Visitor code
	Generated by the 8digits API as a unique device identifier.
 */
@property (nonatomic, strong, readonly)					NSString	*visitorCode;

/**
	Session code
 */
@property (nonatomic, strong, readonly)					NSString	*sessionCode;


/**
	8digits username
	MUST be non-nil by the time the start method is called.
 */
@property (nonatomic, strong)							NSString	*apiKey;


/**
	Authorisation status
 */
@property (nonatomic, readonly, getter = isAutorised)	BOOL		 authorised;

/**
	All EDHit objects belonging to this visit
 */
@property (nonatomic, strong, readonly)					NSArray		*hits;

/**
	All non-registered EDHit objects belonging to this visit
	All hits inside this array have either failed to register or haven't finished yet. The reason for this might be an unreachable network, a failed authorisation or a yet unregistered visit.
 */
@property (nonatomic, strong, readonly)					NSArray		*nonRegisteredHits;

/**
    Longtitude of location
 */
@property (nonatomic, strong)                           NSString    *longitude;


/**
    Latitude of location
 */
@property (nonatomic, strong)                           NSString    *latitude;


/**
	Current visit
	Set automatically when a new visit starts
 */
+ (EDVisit *)currentVisit;


/**
	Starts the visit
	Should be used at the start of the application.
	The EDVisit object being used will be set as currentVisit. Optionally, you can use this as [[EDVisit currentVisit] start]
	The object MUST have non-nil username and password properties set by the time this method is called. username, urlPrefix and trackingCode parameters will be looked for inside EightDigits.plist if not set directly.
	@see startWithUsername:password:
	@see startWithUsername:password:trackingCode:urlPrefix:
 */
- (void)start;

/**
	Sets the username and password and calls the start method
	@param username 8digits username
	@param password 8digits password
 */
- (void)startWithApiKey:(NSString *)apiKey;

/**
	Sets the username, password, trackingCode and urlPrefix parameters and calls the start method
	@param username 8digits username
	@param password 8digits password
	@param trackingCode 8digits tracking code; uses the default value (string value with EDTrackingCode key inside EightDigits.plist) if nil
	@param urlPrefix 8digits URL prefix; uses the default value (string value with EDURLPrefix key inside EightDigits.plist) if nil
 */
- (void)startWithApiKey:(NSString *)apiKey trackingCode:(NSString *)trackingCode urlPrefix:(NSString *)urlPrefix;

/**
	Starts the visit directly with an already authorised token
	Use this if you don't want your username and password hardcoded inside the app for security purposes
	@param authToken auth token to be used for this visit
 */
- (void)startWithAuthToken:(NSString *)authToken;

/**
 Sets location of visitor.
 Use this method before starting new visit.
 @param longtitude  long value of location
 @param latitude    lat value of location
 */
- (void)setLocationWithLongitude:(NSString *)longitude andLatitude:(NSString *)latitude;

/**
	Ends the visit
 */
- (void)end;

/**
	Creates and submits an event with given key-value pair
	There will be no hitCode used with the event. This means that the event will not be associated with any controllers or screens. If you want to trigger an event associated with a screen, please see UIViewController instance method with the same name.
	@see -[UIViewController triggerEventWithValue:forKey:]
	@param value, key The key-value pair of the event
 */
- (void)triggerEventWithValue:(NSString *)value forKey:(NSString *)key;


/**
	Logging status of the visit
	YES if the registration success/failures gets logged, NO if not. Read-only property; set with startLogging and stopLogging.
	@default NO
	@see startLogging
	@see stopLogging
 */
@property (nonatomic, readonly, getter = isLogging)	BOOL	 logging;

/**
	Starts logging all activities
	@see stopLogging
 */
- (void)startLogging;

/**
	Stops logging all activities
	@see startLogging
 */
- (void)stopLogging;

@end
