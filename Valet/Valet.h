//
//  Valet.h
//  Valet
//
//  Created by Dan Federman on 1/21/15.
//  Copyright (c) 2015 Square, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSUInteger, VALAccessibility) {
    /// Valet data can only be accessed while the device is unlocked. This attribute is recommended for data that only needs to be accesible while the application is in the foreground. Valet data with this accessibility will migrate to a new device when using encrypted backups.
    VALAccessibleWhenUnlocked = 1,
    /// Valet data can only be accessed once the device has been unlocked after a restart. This attribute is recommended for data that needs to be accesible by background applications. Valet data with this attribute will migrate to a new device when using encrypted backups.
    VALAccessibleAfterFirstUnlock,
    /// Valet data can always be accessed regardless of the lock state of the device. This attribute is not recommended. Valet data with this attribute will migrate to a new device when using encrypted backups.
    VALAccessibleAlways,
    
    /// Valet data can only be accessed while the device is unlocked. This class is only available if a passcode is set on the device. This is recommended for items that only need to be accessible while the application is in the foreground. Valet data with this attribute will never migrate to a new device, so these items will be missing after a backup is restored to a new device. No items can be stored in this class on devices without a passcode. Disabling the device passcode will cause all items in this class to be deleted.
    VALAccessibleWhenPasscodeSetThisDeviceOnly,
    /// Valet data can only be accessed while the device is unlocked. This is recommended for data that only needs to be accesible while the application is in the foreground. Valet data with this attribute will never migrate to a new device, so these items will be missing after a backup is restored to a new device.
    VALAccessibleWhenUnlockedThisDeviceOnly,
    /// Valet data can only be accessed once the device has been unlocked after a restart. This is recommended for items that need to be accessible by background applications. Valet data with this attribute will never migrate to a new device, so these items will be missing after a backup is restored to a new device.
    VALAccessibleAfterFirstUnlockThisDeviceOnly,
    /// Valet data can always be accessed regardless of the lock state of the device. This option is not recommended. Valet data with this attribute will never migrate to a new device, so these items will be missing after a backup is restored to a new device.
    VALAccessibleAlwaysThisDeviceOnly,
};


/// Reads and writes keychain elements.
@interface Valet : NSObject

/// Creates a Valet that reads/writes keychain elements with the desired accessibility.
- (instancetype)initWithIdentifier:(NSString *)identifier accessibility:(VALAccessibility)accessibility __attribute__((nonnull(1)));

/// Creates a Valet that reads/writes keychain elements that can be shared across applications written by the same development team. The sharedAccessGroupIdentifier must correspond with the value for keychain-access-groups in your Entitlements file.
- (instancetype)initWithSharedAccessGroupIdentifier:(NSString *)sharedAccessGroupIdentifier accessibility:(VALAccessibility)accessibility __attribute__((nonnull(1)));

@property (copy, readonly) NSString *identifier;
@property (readonly, getter=isSharedAcrossApplications) BOOL sharedAcrossApplications;
@property (readonly) VALAccessibility accessibility;

- (BOOL)canAccessKeychain;

- (BOOL)setValue:(NSData *)value forKey:(NSString *)key __attribute__((nonnull(1,2)));
- (NSData *)valueForKey:(NSString *)key __attribute__((nonnull(1)));

- (BOOL)setString:(NSString *)string forKey:(NSString *)key __attribute__((nonnull(1,2)));
- (NSString *)stringForKey:(NSString *)key __attribute__((nonnull(1)));

- (BOOL)hasKey:(NSString *)key __attribute__((nonnull(1)));
- (NSSet *)allKeys;
- (BOOL)removeDataForKey:(NSString *)username __attribute__((nonnull(1)));
- (BOOL)removeAllData;

@end


/// Reads and writes keychain elements that are synchronized with iCloud (supported on devices on iOS 7.0.3 and later). Accessibility must not be scoped to this device.
@interface SynchronizableValet : Valet
@end


/// Reads and writes keychain elements that are stored on the Secure Element (supported on iOS 8.0 or later) using accessibility attribute VALAccessibleWhenPasscodeSetThisDeviceOnly. Accessing or modifying these items will require the user to confirm their presence via Touch ID or passcode entry. Use the userPrompt methods to display custom text to the user in Apple's Touch ID and passcode entry UI.
@interface SecureElementValet : Valet

- (NSData *)valueForKey:(NSString *)key userPrompt:(NSString *)userPrompt __attribute__((nonnull(1)));
- (BOOL)setValue:(NSData *)value forKey:(NSString *)key userPrompt:(NSString *)userPrompt __attribute__((nonnull(1,2)));

- (NSString *)stringForKey:(NSString *)key userPrompt:(NSString *)userPrompt __attribute__((nonnull(1)));
- (BOOL)setString:(NSString *)string forKey:(NSString *)key userPrompt:(NSString *)userPrompt __attribute__((nonnull(1,2)));

@end
