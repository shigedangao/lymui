use napi::bindgen_prelude::*;

pub trait FromJsObject {
    fn from_js_object(object: Object) -> Result<Self>
    where
        Self: Sized;
}

pub mod prelude {
    pub use super::FromJsObject;
    pub use js_macro::FromJsObj;
    pub use napi::bindgen_prelude::{
        Status,
        Object,
        Result as NapiResult
    };
    pub use napi::Error as JsError;
}
